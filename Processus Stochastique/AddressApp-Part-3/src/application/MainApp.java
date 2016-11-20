package application;

import java.io.IOException;

import application.model.Mmsk;
import application.view.MmskEditDialogController;
import application.view.MmskOverviewController;
import javafx.application.Application;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.layout.AnchorPane;
import javafx.scene.layout.BorderPane;
import javafx.stage.Modality;
import javafx.stage.Stage;

/**
 * @author MENIN Valerian
 *
 */
public class MainApp extends Application {

  /**
   * @param args
   */
  public static void main(String[] args) {
    launch(args);
  }

  private Stage primaryStage;

  private BorderPane rootLayout;

  /**
   * The data as an observable list of Persons.
   */
  private ObservableList<Mmsk> listMmsk = FXCollections.observableArrayList();

  /**
   * Constructor
   */
  public MainApp() {
    // Add some sample data
    listMmsk.add(new Mmsk(3, 4, 1, -1, -1, "FIFO"));// L=3
    listMmsk.add(new Mmsk(3, 5, 1, -1, -1, "FIFO"));// L=1.5
    listMmsk.add(new Mmsk(3, 4, 1, 3, -1, "FIFO"));// L=1.15, Lq=0.51, q0=0.36,
                                                   // q3=0.15
    listMmsk.add(new Mmsk(3, 4, 1, -1, -1, "FIFO"));// Lq=2.25, Wq=0.75,
                                                    // ProbaAttendrePlusDUneHeure=0.37
    listMmsk.add(new Mmsk(0.04166666667, 0.08, 1, -1, -1, "FIFO"));// L=0.7142
    listMmsk.add(new Mmsk(8, 24, 1, -1, -1, "FIFO"));// L=0.5, W=0.0625,
                                                     // ProbaPasDArriveePendant1h=0.0003
    listMmsk.add(new Mmsk(10, 12, 1, -1, -1, "FIFO"));// L=5, Lq=4.17, W=0.5,
                                                      // Wq=0.41,
                                                      // ProbaAttendrePlusDe10mn=0.51
                                                      // (/!\10mn=1/6heure),
                                                      // q2=0.11
    listMmsk.add(new Mmsk(10, 12, 2, -1, -1, "FIFO"));// Lq=0.175, W=0.1,
                                                      // Wq=0.017,
                                                      // ProbaAttendrePlusDe10mn=0.19
                                                      // (/!\10mn=1/6heure),
                                                      // q0=0.412, q2=0.14
    listMmsk.add(new Mmsk(72, 120, 1, -1, -1, "FIFO"));// L=1.5
    listMmsk.add(new Mmsk(72, 180, 1, -1, -1, "FIFO"));// L=0.666
  }

  /**
   * Returns the data as an observable list of Persons.
   *
   * @return void
   */
  public ObservableList<Mmsk> getListMmsk() {
    return listMmsk;
  }

  /**
   * Returns the main stage.
   *
   * @return void
   */
  public Stage getPrimaryStage() {
    return primaryStage;
  }

  /**
   * Initializes the root layout.
   */
  public void initRootLayout() {
    try {
      // Load root layout from fxml file.
      FXMLLoader loader = new FXMLLoader();
      loader.setLocation(MainApp.class.getResource("view/RootLayout.fxml"));
      rootLayout = (BorderPane) loader.load();

      // Show the scene containing the root layout.
      Scene scene = new Scene(rootLayout);
      primaryStage.setScene(scene);
      primaryStage.show();
    } catch (IOException e) {
      e.printStackTrace();
    }
  }

  /**
   * Opens a dialog to edit details for the specified mmsk. If the user clicks
   * OK, the changes are saved into the provided mmsk object and true is
   * returned.
   *
   * @param mmsk
   *          the mmsk object to be edited
   * @return true if the user clicked OK, false otherwise.
   */
  public boolean showMmskEditDialog(Mmsk mmsk) {
    try {
      // Load the fxml file and create a new stage for the popup dialog.
      FXMLLoader loader = new FXMLLoader();
      loader.setLocation(MainApp.class.getResource("view/MmskEditDialog.fxml"));
      AnchorPane page = (AnchorPane) loader.load();
      // Create the dialog Stage.
      Stage dialogStage = new Stage();
      dialogStage.setTitle("Edit Mmsk");
      dialogStage.initModality(Modality.WINDOW_MODAL);
      dialogStage.initOwner(primaryStage);
      Scene scene = new Scene(page);
      dialogStage.setScene(scene);
      // Set the person into the controller.
      MmskEditDialogController controller = loader.getController();
      controller.setDialogStage(dialogStage);
      controller.setMmsk(mmsk);
      // Show the dialog and wait until the user closes it
      dialogStage.showAndWait();
      return controller.isOkClicked();
    } catch (IOException e) {
      e.printStackTrace();
      return false;
    }
  }

  /**
   * Shows the mmsk overview inside the root layout.
   */
  public void showMmskOverview() {
    try {
      // Load mmsk overview.
      FXMLLoader loader = new FXMLLoader();
      loader.setLocation(MainApp.class.getResource("view/MmskOverview.fxml"));
      AnchorPane mmskOverview = (AnchorPane) loader.load();

      // Set mmsk overview into the center of root layout.
      rootLayout.setCenter(mmskOverview);

      // Give the controller access to the main app.
      MmskOverviewController controller = loader.getController();
      controller.setMainApp(this);

    } catch (IOException e) {
      e.printStackTrace();
    }
  }

  @Override
  public void start(Stage primaryStage) {
    this.primaryStage = primaryStage;
    this.primaryStage.setTitle("Processus Stochastiques");

    initRootLayout();

    showMmskOverview();
  }
}
