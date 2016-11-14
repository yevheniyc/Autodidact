package com.example.swing;

import java.awt.Component;
import java.awt.Graphics;
import java.awt.Image;
import java.awt.Rectangle;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.geom.AffineTransform;
import java.awt.image.AffineTransformOp;
import java.awt.image.BufferedImage;
import java.awt.image.ColorConvertOp;
import java.io.File;
import java.io.IOException;

import javax.imageio.ImageIO;
import javax.swing.BoxLayout;
import javax.swing.Icon;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextField;
import javax.swing.SwingUtilities;


public class SwingTest {
	private static final String IMAGE_FILENAME = "testimage.jpg";

	public static void main(String[] args) {
		SwingUtilities.invokeLater( () -> {
			SwingTest test = new SwingTest();
			test.createSwingWindow();
		});
	}
	
	
	
	public JFrame createSwingWindow() {
		JFrame frame = new JFrame("Test Swing Application");
		frame.setLayout(new BoxLayout(frame.getContentPane(), BoxLayout.Y_AXIS));
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		JLabel label = new JLabel("This is our test Swing application");
		JButton button = new JButton("Click Me!");
		
		
		ImageIcon icon = new ImageIcon(IMAGE_FILENAME);
		JLabel iconLabel = new JLabel(icon);
		
		JPanel panel = new JPanel();
		panel.setLayout(new BoxLayout(panel, BoxLayout.X_AXIS));
		JLabel pctSizeLabel = new JLabel("Percent Size: ");
		JTextField pctSizeField = new JTextField();
		JLabel rotationLabel = new JLabel("Degree Rotation: ");
		JTextField rotationField = new JTextField();
		
		button.addActionListener(event -> 
				adjustImage(pctSizeField, rotationField, iconLabel));
		
		panel.add(pctSizeLabel);
		panel.add(pctSizeField);
		panel.add(rotationLabel);
		panel.add(rotationField);
		
		frame.add(label);
		frame.add(iconLabel);
		frame.add(panel);
		frame.add(button);
		
		label.setAlignmentX(Component.CENTER_ALIGNMENT);
		iconLabel.setAlignmentX(Component.CENTER_ALIGNMENT);
		button.setAlignmentX(Component.CENTER_ALIGNMENT);
		
		
		
		frame.pack();
		frame.setVisible(true);
		return frame;
	}
	
	
	private void adjustImage(JTextField pctField, JTextField degreeField, 
			JLabel imageLabel) {
		
	}
	
	
	
	private BufferedImage convertToBufferedImage(Image image) {
		if (image instanceof BufferedImage) {
			return (BufferedImage)image;
		}
		
		BufferedImage bi = new BufferedImage(image.getWidth(null), image.getHeight(null), 
				BufferedImage.TYPE_INT_ARGB);
		Graphics g = bi.getGraphics();
		g.drawImage(image, 0, 0, null);
		g.dispose();
		
		return bi;
	}
	
	
	
	
	
	
	
	private int getIntFromTextField(JTextField pctField, int defaultValue) {
		try {
			int num = Integer.parseInt(pctField.getText());
			return num;
		} catch (NumberFormatException e) {
			return defaultValue;
		}
	}
	
	
	
	
	
	
	
	
	
	private BufferedImage resizeImage(BufferedImage bi, int percent) {
		double scale = percent / 100.0;
		AffineTransform resize = AffineTransform.getScaleInstance(scale, scale);
		AffineTransformOp op = new AffineTransformOp (
				resize,
				AffineTransformOp.TYPE_BICUBIC);
		return op.filter(bi, null);
	}
	
	
	
	
	
	
	
	
	
	
	private BufferedImage rotateImage(BufferedImage bi, int degrees) {
		double radians = Math.toRadians(degrees);
		AffineTransform rotate = AffineTransform.getRotateInstance(radians);
		AffineTransformOp op = new AffineTransformOp (
				rotate,
				AffineTransformOp.TYPE_BILINEAR);
		return op.filter(bi, null);
	}
	
	
	
	
	
	
	
	
	
	
	
	
	private BufferedImage rotateImageBetter(BufferedImage bi, int degrees) {
		double radians = Math.toRadians(degrees);
		AffineTransform rotate = AffineTransform.getRotateInstance(radians);
		
		int height = bi.getHeight();
		int width = bi.getWidth();
		Rectangle newSize = rotate.createTransformedShape(
				new Rectangle(width, height)).getBounds();
		
		rotate = new AffineTransform();
		rotate.translate(newSize.width*0.5, newSize.height*0.5);
		rotate.rotate(radians);
		rotate.translate(-width*0.5, -height*0.5);
		
		AffineTransformOp op = new AffineTransformOp(
				rotate, 
				AffineTransformOp.TYPE_BILINEAR);
		return op.filter(bi, null);
	}
	
	
	
	
	
	
	private void saveImage(Image image, File file) throws IOException {
		BufferedImage bi = convertToBufferedImage(image);
		ImageIO.write(bi, "png", file);
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	private void saveJpgImage(Image image, File file) throws IOException {
		BufferedImage bi = convertToBufferedImage(image);
		
		BufferedImage rgbImage = new BufferedImage(
				bi.getWidth(), bi.getHeight(), BufferedImage.TYPE_INT_RGB);
		ColorConvertOp toRGB = new ColorConvertOp(null);
		toRGB.filter(bi, rgbImage);
		
		ImageIO.write(rgbImage, "jpg", file);
	}
	
}
