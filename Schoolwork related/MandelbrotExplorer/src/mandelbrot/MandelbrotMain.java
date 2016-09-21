package mandelbrot;

public class MandelbrotMain {

	
	public static void main(String[] args) {
		int Width = 1024;
		int Height = 682;
		int MaxIter = 100;
		if(args.length == 1) {
			Width = Integer.valueOf(args[0]);
		} else if(args.length == 2) {
			Width  = Integer.valueOf(args[0]);
			Height = Integer.valueOf(args[2]);
		} else if(args.length == 3){
			Width  = Integer.valueOf(args[0]);
			Height = Integer.valueOf(args[1]);
			MaxIter = Integer.valueOf(args[2]);		
		}
		MandelbrotModel Model = new MandelbrotModel(Width, Height, MaxIter);
		MandelbrotView View = new MandelbrotView(Model);
		@SuppressWarnings("unused")
		MandelbrotController Controller = new MandelbrotController(Model, View);
		Model.PanAndZoom(Width/2, Height/2, 1.0f);
		Model.ParallellCalculateSet();
	}
}
