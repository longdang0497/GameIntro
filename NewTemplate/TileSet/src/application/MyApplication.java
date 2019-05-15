package application;

import java.awt.Graphics;
import java.awt.image.BufferedImage;
import java.awt.image.DataBuffer;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.net.URL;
import java.util.ArrayList;
import java.util.List;
import java.util.ResourceBundle;

import javax.imageio.ImageIO;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.Alert;
import javafx.scene.control.Button;
import javafx.scene.control.ButtonType;
import javafx.scene.control.Label;
import javafx.scene.control.ProgressBar;
import javafx.scene.control.TextField;
import javafx.scene.control.Alert.AlertType;
import javafx.stage.DirectoryChooser;
import javafx.stage.FileChooser;
import javafx.stage.FileChooser.ExtensionFilter;

public class MyApplication implements Initializable {

	public static final String OUTPUT_FILE_NAME = "\\result.txt";
	public static final String OUTPUT_IMAGE_NAME = "\\result.png";
	public static final int TOTAL_HEIGT = 0;

	@FXML
	private TextField txtFilePath, txtOutputPath, txtWidth, txtHeight;

	@FXML
	private Button btnOpenFilePath, btnOutputPath, btnExport;

	@FXML
	private Label lbProgress;
	
	@FXML
	private ProgressBar pgbProgress;
	
	@Override
	public void initialize(URL location, ResourceBundle resources) {

	}

	public void getFilePath(ActionEvent event) {
		FileChooser fileChooser = new FileChooser();
		fileChooser.setTitle("Tìm kiếm đường dẫn hình ảnh");

		ExtensionFilter filter = new ExtensionFilter("png và jpg", "*.png", "*.jpg");

		fileChooser.getExtensionFilters().add(filter);

		File file = fileChooser.showOpenDialog(null);
		if (file != null) {
			txtFilePath.setText(file.getAbsolutePath());
		}
	}

	public void getOutputPath(ActionEvent event) {
		DirectoryChooser directoryChooser = new DirectoryChooser();
		directoryChooser.setTitle("Chọn thư mục để lưu kết quả");

		File dir = directoryChooser.showDialog(null);

		if (dir != null) {
			this.txtOutputPath.setText(dir.getAbsolutePath());
		}
	}

	public void exportImage(ActionEvent event) throws IOException {

		
		if ("".equals(txtHeight.getText().trim()) || "".equals(txtWidth.getText().trim())
				|| "".equals(txtFilePath.getText().trim()) || "".equals(txtOutputPath.getText().trim())) {
			Alert alert = new Alert(AlertType.ERROR, "Không được để trống bất kỳ trường nào ở trên", ButtonType.OK);
			alert.show();
			return;
		}

		BufferedImage img = ImageIO.read(new File(txtFilePath.getText()));

		List<BufferedImage> resultImages = new ArrayList<>();

		int tileWidth = Integer.parseInt(txtWidth.getText());
		int tileHeight = Integer.parseInt(txtHeight.getText());

		int[][] matrix = new int[img.getHeight() / tileHeight][img.getWidth() / tileWidth];
		
		
		for (int i = 0; i < img.getHeight(); i += tileHeight) {
			for (int j = 0; j < img.getWidth(); j += tileWidth) {
				BufferedImage subImage = img.getSubimage(j, i, tileWidth, tileHeight);

				System.out.println("position: " + i + " - " + j);

				if (resultImages.isEmpty()) {
					resultImages.add(subImage);
					matrix[i / tileHeight][j / tileWidth] = 0;
				} else {

					boolean flag = false;

					int z = 0;

					for (z = 0; z < resultImages.size(); z++) {
						int difference = 0;
						for (int h = 0; h < tileHeight; h++) {
							for (int w = 0; w < tileWidth; w++) {
								int rgbA = subImage.getRGB(w, h);
								int rgbB = resultImages.get(z).getRGB(w, h);
								int redA = (rgbA >> 16) & 0xff;
								int greenA = (rgbA >> 8) & 0xff;
								int blueA = (rgbA) & 0xff;
								int redB = (rgbB >> 16) & 0xff;
								int greenB = (rgbB >> 8) & 0xff;
								int blueB = (rgbB) & 0xff;

								difference += Math.abs(redA - redB);
								difference += Math.abs(greenA - greenB);
								difference += Math.abs(blueA - blueB);
							}
						}

						double total_pixels = subImage.getWidth() * subImage.getHeight() * 3;

						double avg_different_pixels = difference / total_pixels;

						double percentage = (avg_different_pixels / 255) * 100;

						System.out.println("Difference Percentage ----> " + percentage);

						if (Double.compare(percentage, new Double("0")) == 0) {
							matrix[i / tileHeight][j / tileWidth] = z;
							flag = true;
							break;
						}

					}

					if (!flag) {
						resultImages.add(subImage);
						matrix[i / tileHeight][j / tileWidth] = resultImages.size() - 1;
					}

				}
			}
		}

		// Ghi vào file txt
		BufferedWriter writer = new BufferedWriter(new FileWriter(txtOutputPath.getText() + OUTPUT_FILE_NAME));

		writer.write(
				 img.getWidth() / tileWidth + "\t" + img.getHeight() / tileHeight + "\t" + tileHeight + "\t" + tileWidth + "\t" + (resultImages.size()) + "\t" + 1);
		writer.write(System.getProperty("line.separator"));
		for (int i = 0; i < img.getHeight() / tileHeight; i++) {
			for (int j = 0; j < img.getWidth() / tileWidth; j++) {
				writer.write(matrix[i][j] + "\t");
			}

			writer.write(System.getProperty("line.separator"));
		}

		writer.close();

		// Ghi hình ảnh jpg
		BufferedImage concatImage = new BufferedImage(tileWidth * resultImages.size(), tileHeight,
				BufferedImage.TYPE_INT_RGB);
		Graphics g = concatImage.getGraphics();
		for (int i = 0; i < resultImages.size(); i++) {
			g.drawImage(resultImages.get(i), i * tileWidth, 0, null);
		}
		g.dispose();

		ImageIO.write(concatImage, "png", new File(txtOutputPath.getText() + OUTPUT_IMAGE_NAME));

		new Alert(AlertType.INFORMATION, "Xong rồi <3 ", ButtonType.OK).show();

	}

}
