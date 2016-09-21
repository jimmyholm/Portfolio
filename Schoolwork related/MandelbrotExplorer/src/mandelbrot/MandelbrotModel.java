package mandelbrot;

import java.util.Observable;

import complex.Complex;
import pair.Pair;

import java.awt.Rectangle;
import java.util.List;
import java.util.ArrayList;
import java.util.concurrent.ForkJoinPool;
import java.util.concurrent.RecursiveAction;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

/**
 * The MandelbrotModel class provides the necessary functionality for calculating and accessing the iteration-values and complex distance of a cross-section of the Mandelbrot set
 * 
 * @author 	Jimmy Holm
 * @version 1.0
 * @since 	2013-11-15
 *   
 */
public class MandelbrotModel extends Observable {
	
		/**
		 * The maximum number of concurrent running threads.
		 */
		private int MaxConcurrentThreads;
		/**
		 * The thread-pool used for concurrent calculation of the mandelbrot set.
		 */
		private ForkJoinPool ThreadPool;
	
		/**
		 * Lock to ensure thread-safety of fractal calculations.
		 */
		private Lock ThreadLock;
		
		/**
		 * The array containing the number of iterations for each point in the current section of the Mandelbrot set, as well as the squared-distance from the origin of the complex plane. A value of (MaxIteratrions+1,0.0)  
		 * means the point appears to belong to the set.
		 */
		private List<Pair<Integer, Double> > Fractal;
		
		/**
		 * The maximum amount of iterations to perform before assuming the point belongs to the Mandelbrot set.
		 */
		private int MaxIterations;
		
		/**
		 * The greatest number of iterations for a point outside the set.
		 */
		private int HighestIterationCount;
		
		/**
		 * A rectangle in the complex plane 
		 */
		private class ComplexRect {
			public Complex TopLeft;
			public Complex BottomRight;
			public ComplexRect(Complex TL, Complex BR) {
				TopLeft = TL;
				BottomRight = BR;
			}
		}
		
		/**
		 * The cross-section we're currently interested in.
		 */
		private ComplexRect CrossSection;
		
		/**
		 * The current zoom-factor
		 */
		private double ZoomFactor;
		
		/**
		 * The number of points to calculate in the interval [Re(CrossSection.TopLeft), Re(CrossSection.BottomRight)].
		 */
		private int Width;
		
		/**
		 * The number of points to calculate in the interval [Im(CrossSection.TopLeft), Im(CrossSection.BottomRight)].
		 */
		private int Height;
		
		/**
		 * The number of points in the complex plane between two elements in the interval [0,Width[.
		 */
		private double xStep;
		/**
		 * The number of points in the complex plane between two elements in the interval [0,Height[.
		 */
		private double yStep;
		
		/**
		 *  Create a MandelbrotModel instance.
		 *  <p>
		 *  The Mandelbrot Model requires some knowledge about the resolution of the set to create, as well as how many iterations it 
		 *  should try to calculate before deciding a point is part of the set. 
		 * @param Width Horizontal resolution
		 * @param Height Vertical resolution
		 * @param MaxIterations Exceeding this many iterations is assumed to mean the point is inside the set. A higher value means greater accuracy, but slower calculations.
		 */
		public MandelbrotModel(int Width, int Height, int MaxIterations) {
			CrossSection = new ComplexRect(new Complex(-2.0d, 1.0d), new Complex(1.0d, -1.0d));
			ZoomFactor = 1.0d;
			this.Width = Width;
			this.Height = Height;
			xStep = (CrossSection.BottomRight.getReal() - CrossSection.TopLeft.getReal()) / (double)Width;
			yStep = (CrossSection.TopLeft.getImaginary() - CrossSection.BottomRight.getImaginary()) / (double)Height;
			Fractal = new ArrayList< Pair<Integer, Double> >(Width*Height);
			for(int x = 0; x < Width; x++)
				for(int y = 0; y < Height; y++)
					Fractal.add(new Pair<Integer, Double>(-1, 0.0d));
			this.MaxIterations = MaxIterations;
			ThreadLock = new ReentrantLock();
			ThreadPool = new ForkJoinPool();
			MaxConcurrentThreads = ThreadPool.getParallelism();
		}
		
		/**
		 * Get the width of the fractal. 
		 * @return The fractal's width
		 */
		public int GetWidth() {
			return Width;
		}
		
		/**
		 * Get the height of the fractal.
		 * @return The fractal's height.
		 */
		public int GetHeight() {
			return Height;
		}
		
		/**
		 * Set the maximum number of iterations per computation
		 * @param MaxIterations The new maxmimum number of iterations.
		 */
		public void UpdateMaxIterations(int MaxIterations) {
			this.MaxIterations = MaxIterations;
		}
		
		/**
		 * Return the maximum number of iterations to do per computation.
		 * @return The maximum number of iterations per computation.
		 */
		public int GetMaximumIterations() {
			return MaxIterations;
		}

		/**
		 * Get the greatest number of iterations used to find out that a point is outside the set.
		 * @return The greatest number of iterations used to find out that a point is outside the set.
		 */
		public int GetHighestIterationCount() {
			return HighestIterationCount;
		}
		
		/**
		 * Calculate whether a point is inside the Mandelbrot set.
		 * @param Point The point in the complex plane to be considered
		 * @return The tuple of the number of iterations required to decide if the point is outside the set, or MaxIterations+1 if the point is inside and the absolute-square of the final calculated Z 
		 */
		private Pair<Integer, Double> CalculatePoint(Complex Point) {
			Complex C = new Complex(Point);
			Complex Z = new Complex(C);
			for(int i = 0; i <= MaxIterations; i++) {
				Z = Complex.Add(Complex.Pow(Z, 2), C); // Zn+1 = Zn^2+C
				double m = Complex.Abs2(Z);
				if(m > 4.0d) {
					if(i > HighestIterationCount)
						HighestIterationCount = i;
					return new Pair<Integer, Double>(i, m);
				}
			}
			return new Pair<Integer, Double>(MaxIterations+1, 0.0);
		}
		
		/**
		 * Calculate the iterations needed to determine if the points inside the Area, in resolution-coordinates ( [0, Width[, [0, Height[ ).
		 * @param Area The area of the full fractal to be calculated, including the top-left edges but excluding the bottom-right ones.
		 */
		private void CalculateSection(Rectangle Area) {
			if(Area.x < 0 || Area.x >= Width || Area.y < 0 || Area.y >= Height)
			{
				throw(new IllegalArgumentException("Subscript out of range!"));
			}
			List<Pair<Integer, Double> > Tmp= new ArrayList<Pair<Integer,Double> >(Area.width * Area.height);
			double Y = CrossSection.TopLeft.getImaginary()- (Area.y*yStep);
			for(int y = 0;  y < Area.height; y++) {
				double X = CrossSection.TopLeft.getReal() + (Area.x*xStep);
				for(int x = 0; x < Area.width; x++) {
					Tmp.add(x+y*Area.width, CalculatePoint(new Complex(X, Y)));
					X += xStep;
				}
				Y -= yStep;
			}
			ThreadLock.lock();
			for(int y = Area.y; y < Area.y+Area.height && y < Height; y++) {
				for(int x = Area.x; x < Area.x+Area.width && x < Width; x++) {
					Fractal.set(x+y*Width, Tmp.get((x-Area.x) + (y-Area.y) * Area.width));
				}
			}
			ThreadLock.unlock();
		}
		
		/**
		 * Calculates the Mandelbrot Set for the current cross-section using single-threaded computing..
		 */
		public void CalculateSet() {
			HighestIterationCount = 0;
			setChanged();
			notifyObservers("Working");
			CalculateSection(new Rectangle(0, 0, Width, Height));
			setChanged();
			notifyObservers("Redraw");
		}
		
		AtomicInteger counter;
		
		/**
		 * Fork/Join helper class, performing the division and execution of the mandelbrot calculations.
		 * @author Jimmy Holm
		 * 
		 */
		private class MandelbrotWorker extends RecursiveAction {
			private static final long serialVersionUID = 4883365492084090074L;
			/**
			 * The area of the fractal array to operate on.
			 */
			private Rectangle Area;
			
			/**
			 * Current subdivision depth
			 */
			private int Depth;
			
			/**
			 * Tells the compute function whether to do a vertical or horizontal split of the area.
			 */
			private boolean Vertical;
			
			public MandelbrotWorker(Rectangle Area, int Depth, boolean Vertical) {
				this.Area = new Rectangle(Area);
				this.Depth = Depth;
				this.Vertical = Vertical;
				counter.incrementAndGet();
			}
			
			/**
			 * Splits the fractal area to compute into smaller section, each given its own thread to perform the actual mandelbrot calculations.
			 */
			@Override
			protected void compute() {
				if(Depth > MaxConcurrentThreads*250 || Depth > (Height/2) || (Area.width <= 3|| Area.height <= 3)) {
					CalculateSection(Area);
					counter.decrementAndGet();
				}
				else
				{
					counter.decrementAndGet();
					float w2 = (float)Area.width/2.0f;
					float h2 = (float)Area.height/2.0f;
					float xc = (Area.x+Area.width) - w2;
					float yc = (Area.y+Area.height) - h2;
					Rectangle R1;
					Rectangle R2;
					MandelbrotWorker Q1;
					MandelbrotWorker Q2;
					if(Vertical)
					{
						R1 = new Rectangle(Area.x, Area.y, (int)Math.ceil(w2), Area.height);
						R2 = new Rectangle((int)Math.floor(xc), Area.y, (int)Math.ceil(w2), Area.height);
					}	
					else
					{
						R1 = new Rectangle(Area.x, Area.y, Area.width, (int)Math.ceil(h2));
						R2 = new Rectangle(Area.x, (int)Math.floor(yc), Area.width, (int)Math.ceil(h2));
					}
					Q1 = new MandelbrotWorker(R2, Depth+1, !Vertical);
					Q2 = new MandelbrotWorker(R1, Depth+1, !Vertical);
					Q1.fork();
					Q2.compute();
					Q1.join();
				}
			}	
		}
		
		/**
		 * Uses the ForkJoinPool class to calculate the set in multiple threads.
		 */
		public void ParallellCalculateSet() {
			HighestIterationCount = 0;
			setChanged();
			notifyObservers("Working");
			counter = new AtomicInteger(0);
			counter.set(0);
			ThreadPool.invoke(new MandelbrotWorker(new Rectangle(0, 0, Width, Height), 0, true));
			while(counter.get() > 0);
			setChanged();
			notifyObservers("Redraw");
		}
		/**
		 *  Retrieve the number of iterations in a given (x,y) coordinate of the fractal.
		 *  @param X The X-coordinate, in the range [0, Width[
		 *  @param Y The Y-coordinate, in the range [0, Height[
		 *  @return The number of iterations for a point outside the set, or MaxIterations+1 for a point inside.
		 */	
		public int GetIterations(int X, int Y) {
			if(X < 0 || X >= Width || Y < 0 || Y >= Height)
				throw new IllegalArgumentException("Subscript out of range!");
			return Fractal.get(X+Y*Width).First();
		}
		
		/**
		 * Retrieve the absolute-square value of the complex point at (x,y) in the fractal.
		 * @param X The X-coordinate, in the range [0, Width[
		 * @param Y The Y-Coordinate, in the range [0, Height[
		 * @return The absolute-square value of the complex point at (x,y) in the fractal 
		 */
		public double GetValue(int X, int Y) {
			if(X < 0 || X >= Width || Y < 0 || Y >= Height)
				throw new IllegalArgumentException("Subscript out of range!");
			return Fractal.get(X+Y*Width).Second();
		}
		
		/**
		 * Center the cross-section on a new point in the complex plane.
		 * @param X The point in the cross-section which describes the new horizontal center point in the complex plane, in the range [0, Width[. 
		 * @param Y The point in the cross-section which describes the new vertical center point in the complex plane, in the range [0, Height[.
		 * @param Factor The zoom-in factor; the higher the number the smaller the cross-section is calculated.
		 */
		public void PanAndZoom(int X, int Y, double Factor) {
			if(X < 0 || X >= Width || Y < 0 || Y >= Height)
				throw new IllegalArgumentException("Subscript out of range!");
			if(Factor == 0.0)
				throw new IllegalArgumentException("Factor must be non-zero!");
			ZoomFactor = Factor;
			double Horizontal = (CrossSection.BottomRight.getReal() - CrossSection.TopLeft.getReal()) / ZoomFactor;
			double Vertical	  = (CrossSection.BottomRight.getReal() - CrossSection.TopLeft.getReal()) / ZoomFactor;
			double x = (CrossSection.TopLeft.getReal() + X*xStep);
			double y = (CrossSection.TopLeft.getImaginary() - Y*yStep);
			CrossSection = new ComplexRect(new Complex(x-Horizontal/2, y+Vertical/2), new Complex(x+Horizontal/2, y-Vertical/2));
			xStep = (CrossSection.BottomRight.getReal() - CrossSection.TopLeft.getReal()) / (double)Width;
			yStep = (CrossSection.TopLeft.getImaginary() - CrossSection.BottomRight.getImaginary()) / (double)Height;
		}

		/**
		 * Retrieve the current zoom-factor
		 * @return The current zoom-factor
		 */
		public double GetZoomFactor() {
			return ZoomFactor;
		}
		
		public String toString() {
			String r = "";
			for(int y = 0; y < Height; y++) {
				for(int x = 0; x < Width; x++) {
					//r += (Fractal.get(x+y*Width).First() < MaxIterations+1) ? (char)(98+Fractal.get(x+y*Width).First()) /*Fractal[x+y*Width]*/ : " ";
					r += (Fractal.get(x+y*Width).First() == MaxIterations+1) ? "•" : " ";
				}
				r += "\n";
			}
			return r;
		}
	};
