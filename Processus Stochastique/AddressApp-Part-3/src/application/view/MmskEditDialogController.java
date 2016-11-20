package application.view;

import java.text.DecimalFormat;
import java.time.LocalTime;
import java.util.Calendar;

import application.controller.TextFieldController;
import application.model.Mmsk;
import javafx.beans.value.ObservableValue;
import javafx.fxml.FXML;
import javafx.scene.control.Alert;
import javafx.scene.control.Alert.AlertType;
import javafx.scene.control.Button;
import javafx.scene.control.TextField;
import javafx.scene.input.KeyCode;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Stage;

/**
 * Dialog to edit details of a mmsk.
 *
 * @author MENIN Valerian
 */
public class MmskEditDialogController {

  @FXML
  private AnchorPane anchorPane;
  @FXML
  private TextField processusArrive;
  @FXML
  private TextField processusService;
  @FXML
  private TextField nombreService;
  @FXML
  private TextField borneSupClientSysteme;
  @FXML
  private TextField nbClientsPotentiel;
  @FXML
  private TextField reglePassage;
  @FXML
  private Button okBtn;
  @FXML
  private Button cancelBtn;

  private Stage dialogStage;
  private Mmsk mmsk;
  private boolean okClicked = false;

  /**
   * Called when the user clicks cancel.
   */
  @FXML
  private void handleCancel() {
    dialogStage.close();
  }

  /**
   * Called when the user clicks ok.
   */
  @FXML
  private void handleOk() {
    if (isInputLogicallyValid()) {
      if (isInputCalculablyValid()) {
        mmsk.setProcessusArrive(Double.parseDouble(TextFieldController.getCalc(processusArrive.getText())));
        mmsk.setProcessusService(Double.parseDouble(TextFieldController.getCalc(processusService.getText())));
        mmsk.setNombreService(
            (int) Math.round(Double.parseDouble(TextFieldController.getCalc(nombreService.getText()))));
        mmsk.setBorneSupClientSysteme(Integer.parseInt(TextFieldController.getCalc(borneSupClientSysteme.getText())));
        mmsk.setNbClientsPotentiel(Integer.parseInt(TextFieldController.getCalc(nbClientsPotentiel.getText())));
        mmsk.setReglePassage("FIFO");
        mmsk.setDerniereMAJ(LocalTime.of(Calendar.getInstance().get(Calendar.HOUR_OF_DAY),
            Calendar.getInstance().get(Calendar.MINUTE), Calendar.getInstance().get(Calendar.SECOND)));
        okClicked = true;
        dialogStage.close();
      }
    }
  }

  @FXML
  private void initialize() {
    DecimalFormat df = new DecimalFormat("#.#####");

    // Key to cancel or validate
    anchorPane.setOnKeyPressed(event -> {
      if (event.getCode() == KeyCode.ENTER) {
        handleOk();
      }
      if (event.getCode() == KeyCode.ESCAPE) {
        handleCancel();
      }
    });
    // TextFields
    processusArrive.textProperty()
        .addListener((observable, oldValue, newValue) -> updateProcessusArrive(observable, oldValue, newValue, df));

    processusService.textProperty()
        .addListener((observable, oldValue, newValue) -> updateProcessusService(observable, oldValue, newValue, df));

    nombreService.textProperty()
        .addListener((observable, oldValue, newValue) -> updateNombreService(observable, oldValue, newValue, df));

    borneSupClientSysteme.textProperty().addListener(
        (observable, oldValue, newValue) -> updateBorneSupClientSysteme(observable, oldValue, newValue, df));

    nbClientsPotentiel.textProperty()
        .addListener((observable, oldValue, newValue) -> updateNbClientsPotentiel(observable, oldValue, newValue, df));

  }

  private boolean isInputCalculablyValid() {
    String errorMessage = "";
    double mu = Double.parseDouble(TextFieldController.getCalc(processusArrive.getText()))
        / (Double.parseDouble(TextFieldController.getCalc(processusService.getText()))
            * (int) Math.round(Double.parseDouble(TextFieldController.getCalc(nombreService.getText()))));
    if (mu > 1) {
      errorMessage += "No valid mu=\n  P_arrive/(P_service*Nb_service)!\n  Has to be below 1\n";
    }

    if (errorMessage.length() == 0) {
      return true;
    } else {
      // Show the error message.
      Alert alert = new Alert(AlertType.ERROR);
      alert.initOwner(dialogStage);
      alert.setTitle("Invalid Calculability Fields");
      alert.setHeaderText("Please correct invalid fields");
      alert.setContentText(errorMessage);

      alert.showAndWait();

      return false;
    }
  }

  /**
   * Validates the user input in the text fields.
   *
   * @return true if the input is valid
   */
  private boolean isInputLogicallyValid() {
    String errorMessage = "";

    String tmp = processusArrive.getText();
    if (tmp.length() == 0) {
      errorMessage += "No valid processus arrivée! Can not be null\n";
    } else if (!TextFieldController.isReadyToBeCalculated(tmp)) {
      errorMessage += "No valid processus arrivée! Has to be caculatable\n";
    } else if (Double.parseDouble(TextFieldController.getCalc(tmp)) == 0) {
      errorMessage += "No valid processus arrivée! Can not be 0.0\n";
    }

    tmp = processusService.getText();
    if (tmp.length() == 0) {
      errorMessage += "No valid processus service! Can not be null\n";
    } else if (!TextFieldController.isReadyToBeCalculated(tmp)) {
      errorMessage += "No valid processus service! Has to be caculatable\n";
    } else if (Double.parseDouble(TextFieldController.getCalc(tmp)) == 0) {
      errorMessage += "No valid processus service! Can not be 0.0\n";
    }

    tmp = nombreService.getText();
    if (tmp.length() == 0) {
      errorMessage += "No valid nombre service! Can not be null\n";
    } else if (!TextFieldController.isReadyToBeCalculated(tmp)) {
      errorMessage += "No valid nombre service! Has to be caculatable\n";
    } else if (Double.parseDouble(TextFieldController.getCalc(tmp)) == 0) {
      errorMessage += "No valid nombre service! Can not be 0\n";
    } else if (TextFieldController.getCalc(tmp).contains(".") || TextFieldController.getCalc(tmp).contains("\\.")) {
      errorMessage += "No valid nombre service! Has to be an Integer\n";
    }

    tmp = borneSupClientSysteme.getText();
    if (tmp.length() == 0) {
      errorMessage += "No valid borne sup! Can not be null\n";
    } else if (!TextFieldController.isReadyToBeCalculated(tmp)) {
      errorMessage += "No valid borne sup! Has to be caculatable\n";
    } else if (Double.parseDouble(TextFieldController.getCalc(tmp)) == 0) {
      errorMessage += "No valid borne sup! Can not be 0\n";
    } else if (TextFieldController.getCalc(tmp).contains(".") || TextFieldController.getCalc(tmp).contains("\\.")) {
      errorMessage += "No valid borne sup! Has to be an Integer\n";
    } else if (Double.parseDouble(TextFieldController.getCalc(tmp)) < 0
        && Double.parseDouble(TextFieldController.getCalc(tmp)) != -1) {
      errorMessage += "No valid borne sup! Has to be positive or -1 for Infinity";
    }

    tmp = nbClientsPotentiel.getText();
    if (tmp.length() == 0) {
      errorMessage += "No valid nombre client! Can not be null\n";
    } else if (!TextFieldController.isReadyToBeCalculated(tmp)) {
      errorMessage += "No valid nombre client! Has to be caculatable\n";
    } else if (Double.parseDouble(TextFieldController.getCalc(tmp)) == 0) {
      errorMessage += "No valid nombre client! Can not be 0\n";
    } else if (TextFieldController.getCalc(tmp).contains(".") || TextFieldController.getCalc(tmp).contains("\\.")) {
      errorMessage += "No valid nombre client! Has to be an Integer\n";
    } else if (Double.parseDouble(TextFieldController.getCalc(tmp)) < 0
        && Double.parseDouble(TextFieldController.getCalc(tmp)) != -1) {
      errorMessage += "No valid nombre client! Has to be positive or -1 for Infinity";
    }

    tmp = reglePassage.getText();
    if (!tmp.equals("FIFO") && !tmp.equals("PAPS")) {
      errorMessage += "No valid règle! Has to be FIFO";
    }

    if (errorMessage.length() == 0) {// all fields have logical data. Doesn't
                                     // mean that mu is correct
      return true;
    } else {
      // Show the error message.
      Alert alert = new Alert(AlertType.ERROR);
      alert.initOwner(dialogStage);
      alert.setTitle("Invalid Fields");
      alert.setHeaderText("Please correct invalid fields");
      alert.setContentText(errorMessage);

      alert.showAndWait();

      return false;
    }
  }

  /**
   * Returns true if the user clicked OK, false otherwise.
   *
   * @return okClicked
   */
  public boolean isOkClicked() {
    return okClicked;
  }

  /**
   * Sets the stage of this dialog.
   *
   * @param dialogStage
   */
  public void setDialogStage(Stage dialogStage) {
    this.dialogStage = dialogStage;
  }

  /**
   * Sets the mmsk to be edited in the dialog.
   *
   * @param mmsk
   */
  public void setMmsk(Mmsk mmsk) {
    this.mmsk = mmsk;
    processusArrive.setText(Double.toString(mmsk.getProcessusArrive()));
    processusService.setText(Double.toString(mmsk.getProcessusService()));
    nombreService.setText(Integer.toString(mmsk.getNombreService()));
    borneSupClientSysteme.setText(Integer.toString(mmsk.getBorneSupClientSysteme()));
    nbClientsPotentiel.setText(Integer.toString(mmsk.getNbClientsPotentiel()));
    reglePassage.setText(mmsk.getReglePassage());
  }

  private void updateBorneSupClientSysteme(ObservableValue<? extends String> observable, String oldValue,
      String newValue, DecimalFormat df) {
    if (!borneSupClientSysteme.getText().isEmpty()) {
      String tmp = newValue;
      boolean isUnsigned = false;
      tmp = TextFieldController.getValideStringFormula(tmp, isUnsigned);
      borneSupClientSysteme.setText(tmp);
    }
  }

  private void updateNbClientsPotentiel(ObservableValue<? extends String> observable, String oldValue, String newValue,
      DecimalFormat df) {
    if (!nbClientsPotentiel.getText().isEmpty()) {
      String tmp = newValue;
      boolean isUnsigned = false;
      tmp = TextFieldController.getValideStringFormula(tmp, isUnsigned);
      nbClientsPotentiel.setText(tmp);
    }
  }

  private void updateNombreService(ObservableValue<? extends String> observable, String oldValue, String newValue,
      DecimalFormat df) {
    if (!nombreService.getText().isEmpty()) {
      String tmp = newValue;
      boolean isUnsigned = true;
      tmp = TextFieldController.getValideStringFormula(tmp, isUnsigned);
      nombreService.setText(tmp);
    }
  }

  private void updateProcessusArrive(ObservableValue<? extends String> observable, String oldValue, String newValue,
      DecimalFormat df) {
    if (!processusArrive.getText().isEmpty()) {
      String tmp = newValue;
      boolean isUnsigned = true;
      tmp = TextFieldController.getValideStringFormula(tmp, isUnsigned);
      processusArrive.setText(tmp);
    }
  }

  private void updateProcessusService(ObservableValue<? extends String> observable, String oldValue, String newValue,
      DecimalFormat df) {
    if (!processusService.getText().isEmpty()) {
      String tmp = newValue;
      boolean isUnsigned = true;
      tmp = TextFieldController.getValideStringFormula(tmp, isUnsigned);
      processusService.setText(tmp);
    }
  }
}
