package complex;

/**
 * A simple Complex-number representation allowing for basic mathematical operations in the complex plane.
 * @author 		Jimmy Holm
 * @version 	1.0
 * @since 		2013-11-15
 */
public final class Complex {
	/**
	 * The real component of the Complex number
	 */
	private double Real;
	/**
	 * The imaginary component of the Complex number
	 */
	private double Imaginary;
	
	/**
	 * Constructor for a Complex number of type a+bi.
	 * @param a The real component of the new complex number
	 * @param b The Imaginary component of the new complex number
	 */
	public Complex(double a, double b) {
		Real = a;
		Imaginary = b;
	}
	
	/**
	 * Default constructor, setting the complex number to 0+0i.
	 */
	public Complex() {
		Real = 0.0d;
		Imaginary = 0.0d;
	}
	/**
	 * Copy constructor
	 * @param Z the complex number to be copied.
	 */
	public Complex(Complex Z) {
		Real = Z.Real;
		Imaginary = Z.Imaginary;
	}
	
	/**
	 * Retrieve the Real component of the Complex number.
	 * @return The Imaginary component of the Complex number.
	 */
	public double getReal() {
		return Real;
	}
	
	/**
	 * Retrieve the Imaginary component of the Complex number.
	 * @return The Imaginary component of the Complex number.
	 */
	public double getImaginary() {
		return Imaginary;
	}
	
	/**
	 * Update the Real component of the complex number. 
	 * @param a the new value of the real component.
	 */
	public void setReal(double a) {
		Real = a;
	}
	
	/**
	 * Update the Imaginary component of the complex number 
	 * @param b the new value of the imaginary component
	 */
	public void setImaginary(double b) {
		Imaginary = b;
	}
	
	/**
	 * Create the complex conjugate of a complex number Z.
	 * @param Z the complex number which conjugate we wish to create.
	 * @return The conjugate of Z, so that if Z = a+bi the returned conjugate C = a-bi 
	 */
	public static Complex Conjugate(Complex Z) {
		if(Z == null)
			throw new NullPointerException();
		return new Complex(Z.Real, Z.Imaginary*-1);
	}
	
	/**
	 * Create a complex number as the sum of two given complex numbers.
	 * @param Z1 The first of the two complex numbers to add together.
	 * @param Z2 The second of the two complex numbers to add together.
	 * @return The new complex number Z3 so that Z3 = Z1+Z2
	 */
	public static Complex Add(Complex Z1, Complex Z2) {
		if(Z1 == null || Z2 == null)
			throw new NullPointerException();
		return new Complex(Z1.Real+Z2.Real, Z1.Imaginary+Z2.Imaginary);
	}
	
	/**
	 * Update this complex number as the addition between this and Z.
	 * @param Z the complex number to add to this number.
	 */
	public void Add(Complex Z) {
		if (Z == null)
			throw new NullPointerException();
		Real += Z.Real;
		Imaginary += Z.Imaginary;
	}
	
	/**
	 * Create a complex number as the difference of two given complex numbers
	 * @param Z1 The complex numbers to subtract from
	 * @param Z2 The complex number that is to be subtracted.
	 * @return The new complex number Z3 so that Z3 = Z1-Z2
	 */
	public static Complex Sub(Complex Z1, Complex Z2) {
		if(Z1 == null || Z2 == null)
			throw new NullPointerException();
		return new Complex(Z1.Real-Z2.Real, Z1.Imaginary-Z2.Imaginary);
	}
	
	/**
	 * Update this complex number as the subtraction of Z from this.
	 * @param Z The complex number to be subtracted
	 */
	public void Sub(Complex Z) {
		if(Z == null)
			throw new NullPointerException();
		Real -= Z.Real;
		Imaginary -= Z.Imaginary;
	}
	
	/**
	 * Create a complex number as the product of two given complex numbers
	 * @param Z1 The first of the two complex numbers to multiply together
	 * @param Z2 The second of the two complex numbers to multiply together
	 * @return The new complex number Z3 so that Z3 = Z1×Z2
	 */
	public static Complex Mul(Complex Z1, Complex Z2) {
		if(Z1 == null || Z2 == null)
			throw new NullPointerException();
		return new Complex(Z1.Real*Z2.Real-Z1.Imaginary*Z2.Imaginary, Z1.Imaginary*Z2.Real+Z1.Real*Z2.Imaginary);
	}
	
	/**
	 * Update this complex number to the product of multiplication with Z
	 * @param Z The number to multiply this complex number by.
	 */
	public void Mul(Complex Z) {
		if(Z == null)
			throw new NullPointerException();
		Real = Real*Z.Real - Imaginary*Z.Imaginary;
		Imaginary = Imaginary*Z.Real+Real*Z.Imaginary;
	}
	
	/**
	 * Create a new complex number as the quotient of a division of the two complex numbers. 
	 * @param Z1 The numerator of the division
	 * @param Z2 The denominator of the division.
	 * @return The new complex number Z3 so that Z3 = Z1÷Z2
	 * @throws Throws IllegalArgumentException if |Z2| = 0.
	 */
	public static Complex Div(Complex Z1, Complex Z2) {
		if(Z1 == null || Z2 == null)
			throw new NullPointerException();
		Double c = new Double(Z2.Real);
		Double d = new Double(Z2.Imaginary);
		if((c.compareTo(0.0d) == 0 || c.compareTo(-0.0d) == 0) && (d.compareTo(0.0d) == 0 || d.compareTo(-0.0d) == 0))
			throw(new IllegalArgumentException("Argument \"Z2\" is 0; division by 0 error."));
		double c2 = Z2.Real*Z2.Real;
		double d2 = Z2.Imaginary*Z2.Imaginary;
		return new Complex( (Z1.Real*Z2.Real+Z1.Imaginary*Z2.Imaginary) / (c2+d2) , (Z1.Imaginary*Z2.Real - Z1.Real*Z2.Imaginary) / (c2+d2));
	}
	
	/**
	 * Update this complex number to be the quotient of division by Z.
	 * @param Z The denominator in the division.
	 * @throws Throws IllegalArgumentException if |Z| = 0.
	 */
	public void Div(Complex Z) {
		if(Z == null)
			throw new NullPointerException();
		Double c = new Double(Z.Real);
		Double d = new Double(Z.Imaginary);
		if((c.compareTo(0.0d) == 0 || c.compareTo(-0.0d) == 0) && (d.compareTo(0.0d) == 0 || d.compareTo(-0.0d) == 0))
			throw(new IllegalArgumentException("Argument \"Z\" is 0; division by 0 error."));
		double c2 = Z.Real*Z.Real;
		double d2 = Z.Imaginary*Z.Imaginary;
		Real = (Real*Z.Real + Imaginary*Z.Imaginary) / (c2+d2);
		Imaginary = (Imaginary*Z.Real - Real*Z.Imaginary) / (c2+d2);
	}
	
	/**
	 * Calculate the magnitude (absolute value) of the given complex number.
	 * @param Z the complex number whose absolute value is to be calculated.
	 * @return The absolute value of Z (|Z|)
	 */
	public static double Abs(Complex Z) {
		if(Z == null)
			throw new NullPointerException();
		Double c = new Double(Z.Real);
		Double d = new Double(Z.Imaginary);
		if((c.compareTo(0.0d) == 0 || c.compareTo(-0.0d) == 0) && (d.compareTo(0.0d) == 0 || d.compareTo(-0.0d) == 0))
			return 0.0;
		double a2 = Z.Real*Z.Real;
		double b2 = Z.Imaginary*Z.Imaginary;
		return Math.sqrt(a2+b2);
	}
	
	/** 
	 * Calculate the squared magnitude of Z
	 * @param Z the complex number whose squared magnitude is to be calculated.
	 * @return The squared magnitude of Z (|Z|²)
	 */
	public static double Abs2(Complex Z) {
		if(Z == null)
			throw new NullPointerException();
		Double c = new Double(Z.Real);
		Double d = new Double(Z.Imaginary);
		if((c.compareTo(0.0d) == 0 || c.compareTo(-0.0d) == 0) && (d.compareTo(0.0d) == 0 || d.compareTo(-0.0d) == 0))
			return 0.0;
		double a2 = Z.Real*Z.Real;
		double b2 = Z.Imaginary*Z.Imaginary;
		return a2+b2;
	}
	
	/**
	 * Calculate the square root of the given complex number.
	 * @param Z the complex number whose square root we're interested in.
	 * @return The square root of the complex number Z.
	 */
	public static Complex Sqrt(Complex Z) {
		if(Z == null)
			throw new NullPointerException();
		Double d = new Double(Z.Imaginary);
		if(d.compareTo(0.0d) == 0 || d.compareTo(-0.0d) == 0)
			throw(new IllegalArgumentException("Argument \"Z\" has no imaginary component."));
		double gamma = Math.sqrt(   (Z.Real + Complex.Abs(Z)) / 2);
		double delta = Math.sqrt((-1*Z.Real + Complex.Abs(Z)) / 2);
		return new Complex(gamma, delta);
	}
	
	/**
	 * Return the complex number that represents Z to the nth power.
	 * @param Z The complex number to be raised
	 * @param n The exponent of the new complex number
	 * @return An approximation of the complex number Z3 so that Z3 = (Z)^n
	 */
	public static Complex Pow(Complex Z, int n) {
		if(Z == null)
			throw new NullPointerException();
		if (n == 1)
			return new Complex(Z);
		else if(n == 0)
			return new Complex(1,0);

		double gamma = Math.atan2(Z.Imaginary, Z.Real);
		double r = Complex.Abs(Z);
		r = Math.pow(r, n);
		double nr = (Math.round((r*Math.cos(n*gamma))*100000000000000.0d)) / 100000000000000.0d;
		double ni = (Math.round((r*Math.sin(n*gamma))*100000000000000.0d)) / 100000000000000.0d;
		return new Complex(nr,ni);
	}
	
	/**
	 * Update this complex number to be the approximate result of raising it to the nth power
	 * @param n the exponent to raise this complex number by.
	 */
	public void Pow(int n) {
		if (n == 1)
			return;
		else if(n == 0) {
			Real = 1.0d;
			Imaginary = 0.0d;
			return;
		}
		double gamma = Math.atan2(Imaginary, Real);
		double r = Complex.Abs(this);
		r = Math.pow(r, n);
		Real 	  = (Math.round((r*Math.cos(n*gamma))*100000000000000.0d)) / 100000000000000.0d;
		Imaginary = (Math.round((r*Math.sin(n*gamma))*100000000000000.0d)) / 100000000000000.0d;
	}
	
	/**
	 * Calculate the argument of Z
	 * @param Z The complex number whose argument we want to calculate.
	 * @return The argument of Z.
	 */
	public static double Arg(Complex Z) {
		if(Z == null)
			throw new NullPointerException();
		return Math.atan2(Z.Imaginary, Z.Real);
	}
	
	/**
	 * Provides a textual representation of the complex number in the form a+bi.
	 * @return A string representing the number in the form "Complex(a+bi)". 
	 */
	@Override
	public String toString() {
		return "Complex(" + Real + ((Math.signum(Imaginary) >= 0)?"+":"") + Imaginary + "i)"; 
	}
	
	/**
	 * Compare equality between this and another complex number.
	 * @param Z The complex number to be compared against.
	 * @return true if this and Z refer to the same point in the complex plane.
	 */
	public boolean equals(Complex Z) {
		if(Z == null )
			return false;
		Double c = new Double(Z.Real);
		Double d = new Double(Z.Imaginary);
		return 	(c.compareTo(Real) == 0 &&
				 d.compareTo(Imaginary) == 0);
	}
	
	@Override
	public boolean equals(Object o) {
		if(o == null || !(o instanceof Complex))
			return false;
		Double c = new Double(((Complex)o).Real);
		Double d = new Double(((Complex)o).Imaginary);
		return (c.compareTo(Real) == 0 &&
				d.compareTo(Imaginary) == 0);
	}
}
