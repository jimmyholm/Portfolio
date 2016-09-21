package mandelbrot;

import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;

/**
 * The MandelbrotController class acts as controller of and intermediary between MandelbrotModel and MandelbrotView. 
 * @author Jimmy Holm
 * @version 1.0
 * @since 2013-11-15
 */

public class MandelbrotController implements KeyListener, MouseListener{
	private MandelbrotModel Model;
	private MandelbrotView  View;
	
	
	MandelbrotController(MandelbrotModel Model, MandelbrotView View) {
		this.Model = Model;
		this.View  = View;
		View.AddKeyListener(this);
		View.AddMouseListener(this);
	}
	
	
	@Override
	public void mouseClicked(MouseEvent e) {
		// TODO Auto-generated method stub
		int x = e.getX();
		int y = e.getY();
		if(x < 0 || x > Model.GetWidth() || y < 0 || y > Model.GetHeight())
			return;
		if(e.getButton() == MouseEvent.BUTTON1) {
			Model.PanAndZoom(x, y, 2.0);
		} else if(e.getButton() == MouseEvent.BUTTON2) {
			Model.PanAndZoom(x,  y, 1.0);//Model.GetZoomFactor());
		} else if(e.getButton() == MouseEvent.BUTTON3) {
			Model.PanAndZoom(Model.GetWidth()/2, Model.GetHeight()/2, 0.5);
		}
		Model.ParallellCalculateSet();
	}

	@Override
	public void mouseEntered(MouseEvent e) {
	}

	@Override
	public void mouseExited(MouseEvent e) {
	}

	@Override
	public void mousePressed(MouseEvent e) {
	}

	@Override
	public void mouseReleased(MouseEvent e) {
	}

	@Override
	public void keyPressed(KeyEvent e) {
		if(e.getKeyCode() == KeyEvent.VK_PLUS || e.getKeyCode() == KeyEvent.VK_ADD){
			if((e.getModifiersEx() & KeyEvent.CTRL_DOWN_MASK) == KeyEvent.CTRL_DOWN_MASK && 
			   (e.getModifiersEx() & KeyEvent.SHIFT_DOWN_MASK) != KeyEvent.SHIFT_DOWN_MASK)
				Model.UpdateMaxIterations(Model.GetMaximumIterations() + 10);
			else if((e.getModifiersEx() & KeyEvent.CTRL_DOWN_MASK) != KeyEvent.CTRL_DOWN_MASK && 
					(e.getModifiersEx() & KeyEvent.SHIFT_DOWN_MASK) == KeyEvent.SHIFT_DOWN_MASK)
						Model.UpdateMaxIterations(Model.GetMaximumIterations() + 1);
			else if((e.getModifiersEx() & KeyEvent.CTRL_DOWN_MASK) == KeyEvent.CTRL_DOWN_MASK && 
					(e.getModifiersEx() & KeyEvent.SHIFT_DOWN_MASK) == KeyEvent.SHIFT_DOWN_MASK)
				Model.UpdateMaxIterations(Model.GetMaximumIterations()*10);
			else
				Model.UpdateMaxIterations(Model.GetMaximumIterations()+100);
			View.UpdateTitle();
		} else if((e.getKeyCode() == KeyEvent.VK_MINUS || e.getKeyCode() == KeyEvent.VK_SUBTRACT) && Model.GetMaximumIterations() > 1) {
			if((e.getModifiersEx() & KeyEvent.CTRL_DOWN_MASK) == KeyEvent.CTRL_DOWN_MASK && 
					(e.getModifiersEx() & KeyEvent.SHIFT_DOWN_MASK) != KeyEvent.SHIFT_DOWN_MASK)
				Model.UpdateMaxIterations(Math.max(Model.GetMaximumIterations() - 10, 1));
			else if((e.getModifiersEx() & KeyEvent.CTRL_DOWN_MASK) != KeyEvent.CTRL_DOWN_MASK && 
					(e.getModifiersEx() & KeyEvent.SHIFT_DOWN_MASK) == KeyEvent.SHIFT_DOWN_MASK)
				Model.UpdateMaxIterations(Math.max(Model.GetMaximumIterations() - 1, 1));
			else if((e.getModifiersEx() & KeyEvent.CTRL_DOWN_MASK) == KeyEvent.CTRL_DOWN_MASK && 
					(e.getModifiersEx() & KeyEvent.SHIFT_DOWN_MASK) == KeyEvent.SHIFT_DOWN_MASK)
				Model.UpdateMaxIterations(Math.max(Model.GetMaximumIterations()/10, 1));
			else
				Model.UpdateMaxIterations(Math.max(Model.GetMaximumIterations()-100, 1));
			View.UpdateTitle();
		} else if(e.getKeyCode() == KeyEvent.VK_R) {
			Model.ParallellCalculateSet();
		}
	}

	@Override
	public void keyReleased(KeyEvent e) {
	}

	@Override
	public void keyTyped(KeyEvent e) {
	}

}
