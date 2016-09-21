package mandelbrot;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.event.KeyListener;
import java.awt.event.MouseListener;
import java.awt.image.BufferedImage;
import java.util.Observable;
import java.util.Observer;

import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.SwingUtilities;
/**
 * The MandelbrotView class provides an observer of the MandelbrotModel class, using Swing to render a window and draw a visual representation of the Mandelbrot set.
 * @author Jimmy Holm
 * @version 1.0
 * @since  2013-11-15
 *
 */
public class MandelbrotView implements Observer {
	
	/**
	 * Instance of the MandelbrotModel object to render
	 */
	private MandelbrotModel Model;
	
	/**
	 * The Swing frame of the window.
	 */	
	private final JFrame Frame;

	/**
	 * Helper-class extending JPanel to simplify drawing a buffered image.
	 * @author Jimmy Holm
	 *
	 */
	private class ImagePanel extends JPanel {
		private static final long serialVersionUID = -1096378792277738265L;
		private BufferedImage Image;
		
		public ImagePanel(BufferedImage Image) {
			this.Image = Image;
		}
		
		public BufferedImage GetImage() {
			return Image;
		}
		
		@Override
		public void paintComponent(Graphics g) {
			super.paintComponent(g);
			Graphics2D g2 = (Graphics2D)g;
			g2.drawImage(Image, 0, 0, null);
		}
	}
	
	/**
	 * The Image panel where the Model will be drawn.
	 */
	private final ImagePanel Panel;
	
	/**
	 * The buffered image that will hold the data to be drawn
	 */
	private BufferedImage Image;
	
	public MandelbrotView(MandelbrotModel Model) {
		this.Model = Model;
		this.Model.addObserver(this);
		final int width = Model.GetWidth();
		final int height = Model.GetHeight();
		final JFrame Frame = new JFrame("Mandelbrot Explorer. Maximum Iterations: " + this.Model.GetMaximumIterations());
		Panel = new ImagePanel(new BufferedImage(width, height, BufferedImage.TYPE_INT_RGB));
		Image = Panel.GetImage();
		for(int x = 0; x < width; x++)
			for(int y = 0; y < height; y++) {
				Panel.GetImage().setRGB(x, y, 0x000000);
			}
		try {
			SwingUtilities.invokeAndWait(new Runnable() {
				@Override
				public void run() {
					Frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
					Frame.getContentPane().setPreferredSize(new Dimension(width, height));
					Panel.setPreferredSize(new Dimension(width,height));
					Frame.getContentPane().add(Panel);
					Frame.getContentPane().setBackground(new Color(0,0,0,0));
					Panel.setBackground(new Color(255,0,0,0));
					Panel.setForeground(new Color(255,0,0,0));
					Panel.setVisible(true);
					Frame.setResizable(false);
					Frame.setVisible(true);
					Frame.pack();
				}
			});
		} catch(Exception e) {
			System.out.println("Failed to setup MandelbrotView with exception: " + e);
		}
		this.Frame = Frame;	
	}
	
	/**
	 * Add a key-listener to the Swing-frame
	 * @param Listener The key listener to be added.
	 */	
	public void AddKeyListener(KeyListener Listener) {
		Frame.addKeyListener(Listener);
	}
	
	/**
	 * Add a mouse listener to the Swing-frame
	 * @param Listener The mouse listener to be added.
	 */
	public void AddMouseListener(MouseListener Listener) {
		Frame.addMouseListener(Listener);
	}
	
	/**
	 * Update the window-title to reflect changes in the maximum iteration.
	 */
	public void UpdateTitle() {
		Frame.setTitle("Mandelbrot Explorer. Maximum Iterations: " + this.Model.GetMaximumIterations());
	}
	
	/**
	 * When notified of the change in the model, update the buffered image and repaint the frame.
	 */
	@Override
	public void update(Observable o, Object arg) {
		if(o instanceof MandelbrotModel && arg instanceof String)
		{
			String a = (String)arg;
			switch(a){
				case "Working":
				Frame.setTitle("Mandelbrot Explorer. Maximum Iterations: " + this.Model.GetMaximumIterations() + " *WORKING*");
				break;
				case "Redraw":
					int rgb = 0x000000;
					int I = 0;
					int MI = Model.GetMaximumIterations();
					double Z = 0.0;
					for(int x = 0; x < Image.getWidth(); x++)
						for(int y = 0; y < Image.getHeight(); y++) {
							I = Model.GetIterations(x, y);
							Z = Model.GetValue(x, y);
							if(I != MI+1) {
								double ia = I;
								int W = Image.getWidth();
								int H = Image.getHeight();
								double i0 = Model.GetValue(Math.min(Math.max(0,x-1), W-1), Math.min(Math.max(0,y-1) , H-1));
								double i1 = Model.GetValue(Math.min(Math.max(0,x)  , W-1),	Math.min(Math.max(0,y-1), H-1));
								double i2 = Model.GetValue(Math.min(Math.max(0,x+1), W-1),	Math.min(Math.max(0,y-1), H-1));
								double i3 = Model.GetValue(Math.min(Math.max(0,x+1), W-1), Math.min(Math.max(0,y)	, H-1));
								double i4 = Model.GetValue(Math.min(Math.max(0,x+1), W-1), Math.min(Math.max(0,y+1) , H-1));
								double i5 = Model.GetValue(Math.min(Math.max(0,x)  , W-1), Math.min(Math.max(0,y+1) , H-1));
								double i6 = Model.GetValue(Math.min(Math.max(0,x-1), W-1), Math.min(Math.max(0,y+1) , H-1));
								double i7 = Model.GetValue(Math.min(Math.max(0,x-1), W-1), Math.min(Math.max(0,y)	, H-1));
								ia = (Z+i0+i1+i2+i3+i4+i5+i6+i7) / 9.0;
								double nu = Math.log( Math.log(ia) / (2*Math.log(2))) / Math.log(2);
								float f = ((float)I+(float)(1.0 - nu)) / MI;
								rgb = Color.HSBtoRGB(0.5f+f%0.25f, 0.8f, 0.85f);
							}
							else
								rgb = 0;
							Image.setRGB(x, y, rgb);
						}
					Frame.repaint();
					UpdateTitle();
					break;
				default:
					break;
			}
		}
	}
}
