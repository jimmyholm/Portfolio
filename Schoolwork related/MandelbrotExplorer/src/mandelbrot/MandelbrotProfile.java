package mandelbrot;

import org.junit.Test;

public class MandelbrotProfile {

	@Test
	public void MBT1() {
		MandelbrotModel M = new MandelbrotModel(512, 512, 10000);
		M.CalculateSet();
	}
	
	@Test
	public void MBT2() {
		MandelbrotModel M = new MandelbrotModel(512, 512, 10000);
		M.ParallellCalculateSet();
	}
}
