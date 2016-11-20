package application.view;

import java.text.DecimalFormat;
import java.time.LocalTime;

import javax.script.ScriptEngine;
import javax.script.ScriptEngineManager;
import javax.script.ScriptException;

import application.MainApp;
import application.controller.MmskController;
import application.controller.TextFieldController;
import application.model.Mmsk;
import javafx.beans.value.ObservableValue;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.MenuItem;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.TextField;
import javafx.scene.control.Tooltip;
import javafx.scene.input.KeyCode;
import javafx.scene.input.KeyCodeCombination;
import javafx.scene.input.KeyCombination;
import javafx.scene.layout.AnchorPane;

/**
 * @author MENIN Valerian
 *
 */
public class MmskOverviewController {
  @FXML
  private MenuItem exitApp;
  @FXML
  private MenuItem newMI;
  @FXML
  private MenuItem editMI;
  @FXML
  private MenuItem deleteMI;

  // Button
  @FXML
  private Button newBtn;

  @FXML
  private AnchorPane anchorPane;

  @FXML
  private TableView<Mmsk> mmskTable;

  @FXML
  private TableColumn<Mmsk, LocalTime> derniereMAJ;
  @FXML
  private TableColumn<Mmsk, Number> processusArrive;
  @FXML
  private TableColumn<Mmsk, Number> processusService;
  @FXML
  private TableColumn<Mmsk, Number> nombreService;
  @FXML
  private TableColumn<Mmsk, Number> borneSupClientSysteme;
  @FXML
  private TableColumn<Mmsk, Number> nbClientsPotentiel;

  @FXML
  private TableColumn<Mmsk, String> reglePassage;
  @FXML
  private Label lbl1;
  @FXML
  private Label lbl2;
  @FXML
  private Label lbl3;
  @FXML
  private Label lbl4;
  @FXML
  private Label lbl5;
  @FXML
  private Label lbl6;
  @FXML
  private Label lbl7;
  @FXML
  private Label lbl8;
  @FXML
  private Label lbl9;

  @FXML
  private Label lbl10;
  // TextField
  @FXML
  private TextField qi;
  @FXML
  private TextField probaDansSysSup;
  @FXML
  private TextField probaSansService;
  @FXML
  private TextField poissonTime;
  @FXML
  private TextField poissonNb;

  @FXML
  private Button editBtn;
  @FXML
  private Button deleteBtn;

  // Reference to the main application.
  private MainApp mainApp;

  /**
   * Called when the user clicks on the delete button.
   */
  @FXML
  private void handleDeleteMmsk() {
    int selectedIndex = mmskTable.getSelectionModel().getSelectedIndex();
    if (selectedIndex >= 0) {
      mmskTable.getItems().remove(selectedIndex);
    }
  }

  /**
   * Called when the user clicks the edit button. Opens a dialog to edit details
   * for the selected Mmsk.
   */
  @FXML
  private void handleEditMmsk() {
    Mmsk selectedMmsk = mmskTable.getSelectionModel().getSelectedItem();
    if (selectedMmsk != null) {
      boolean okClicked = mainApp.showMmskEditDialog(selectedMmsk);
      if (okClicked) {
        showMmskDetails(selectedMmsk);
      }
    }
  }

  /**
   * Called when the user clicks the new button. Opens a dialog to edit details
   * for a new Mmsk.
   */
  @FXML
  private void handleNewMmsk() {
    Mmsk tempPerson = new Mmsk();
    boolean okClicked = mainApp.showMmskEditDialog(tempPerson);
    if (okClicked) {
      mainApp.getListMmsk().add(tempPerson);
    }
  }

  /**
   * Initializes the controller class. This method is automatically called after
   * the fxml file has been loaded.
   */
  @FXML
  private void initialize() {
    exitApp.setAccelerator(new KeyCodeCombination(KeyCode.Q, KeyCombination.CONTROL_DOWN));
    exitApp.setOnAction(event -> System.exit(0));

    newMI.setAccelerator(new KeyCodeCombination(KeyCode.N));
    newMI.setOnAction(event -> handleNewMmsk());

    editMI.setAccelerator(new KeyCodeCombination(KeyCode.E));
    editMI.setOnAction(event -> handleEditMmsk());

    deleteMI.setAccelerator(new KeyCodeCombination(KeyCode.DELETE));
    deleteMI.setOnAction(event -> handleDeleteMmsk());

    DecimalFormat df = new DecimalFormat("#.#####");

    // Initialize the mmsk table with the seven columns.
    derniereMAJ.setCellValueFactory(cellData -> cellData.getValue().getDerniereMAJProperty());
    processusArrive.setCellValueFactory(cellData -> cellData.getValue().getProcessusArriveProperty());
    processusService.setCellValueFactory(cellData -> cellData.getValue().getProcessusServiceProperty());
    nombreService.setCellValueFactory(cellData -> cellData.getValue().getNombreServiceProperty());
    borneSupClientSysteme.setCellValueFactory(cellData -> cellData.getValue().getBorneSupClientSystemeProperty());
    nbClientsPotentiel.setCellValueFactory(cellData -> cellData.getValue().getNbClientsPotentielProperty());
    reglePassage.setCellValueFactory(cellData -> cellData.getValue().getReglePassageProperty());

    // Clear person details.
    showMmskDetails(null);

    // Listen for selection changes and show the mmsk details when changed.
    mmskTable.getSelectionModel().selectedItemProperty()
        .addListener((observable, oldValue, newValue) -> showMmskDetails(newValue));

    // Doubleclick on mmsk for edition
    mmskTable.setOnMousePressed(event -> {
      if (event.isPrimaryButtonDown() && event.getClickCount() == 2) {
        handleEditMmsk();
      }
    });

    // EnterKey on mmsk for edition
    mmskTable.setOnKeyPressed(event -> {
      if (event.getCode() == KeyCode.ENTER && mmskTable.isFocused()) {
        handleEditMmsk();
      }
    });

    // Listen for TextFiel changes
    qi.textProperty().addListener((observable, oldValue, newValue) -> updateQi(observable, oldValue, newValue, df));

    probaDansSysSup.textProperty()
        .addListener((observable, oldValue, newValue) -> updateProbaDansSysSup(observable, oldValue, newValue, df));

    probaSansService.textProperty()
        .addListener((observable, oldValue, newValue) -> updateProbaSansService(observable, oldValue, newValue, df));

    poissonTime.textProperty()
        .addListener((observable, oldValue, newValue) -> updatePoissonTime(observable, oldValue, newValue, df));

    poissonNb.textProperty()
        .addListener((observable, oldValue, newValue) -> updatePoissonNb(observable, oldValue, newValue, df));

    setToolTips();
  }

  /**
   * Is called by the main application to give a reference back to itself.
   *
   * @param mainApp
   */
  public void setMainApp(MainApp mainApp) {
    this.mainApp = mainApp;

    // Add observable list data to the table
    mmskTable.setItems(mainApp.getListMmsk());
  }

  /**
   * Sets the tool tips.
   */
  private void setToolTips() {
    qi.setTooltip(new Tooltip("is rounded"));
    poissonTime.setTooltip(new Tooltip("is rounded"));
    poissonNb.setTooltip(new Tooltip("is rounded"));
  }

  /**
   * Fills all text fields to show details about the person. If the specified
   * person is null, all text fields are cleared.
   *
   * @param mmsk
   *          the mmsk or null
   */
  private void showMmskDetails(Mmsk mmsk) {
    if (mmsk != null) {
      // Fill the labels with info from the mmsk object.
      DecimalFormat df = new DecimalFormat("#.#####");
      MmskController.updateCalcValue(mmsk);
      lbl1.setText(df.format(mmsk.getRo()));
      lbl2.setText(df.format(mmsk.getQ0()));
      lbl3.setText(df.format(mmsk.getL()));
      lbl4.setText(df.format(mmsk.getLq()));
      lbl5.setText(df.format(mmsk.getW()));
      lbl6.setText(df.format(mmsk.getWq()));

      updateQi(null, qi.getText(), qi.getText(), df);
      updateProbaDansSysSup(null, probaDansSysSup.getText(), probaDansSysSup.getText(), df);
      updateProbaSansService(null, probaSansService.getText(), probaSansService.getText(), df);
      updatePoissonTime(null, poissonTime.getText(), poissonTime.getText(), df);
      updatePoissonNb(null, poissonNb.getText(), poissonNb.getText(), df);

      // qi probaDansSysSup probaSansService poissonTime poissonNb;
    } else {
      // Mmsk is null, remove all the text.
      lbl1.setText("");
      lbl2.setText("");
      lbl3.setText("");
      lbl4.setText("");
      lbl5.setText("");
      lbl6.setText("");
      lbl7.setText("");
      lbl8.setText("");
      lbl9.setText("");
      lbl10.setText("");
    }

  }

  private void updatePoissonNb(ObservableValue<? extends String> observable, String oldValue, String newValue,
      DecimalFormat df) {
    if (!poissonNb.getText().isEmpty() && mmskTable.getSelectionModel().getSelectedItem() != null) {
      String tmp = newValue;
      boolean isUnsigned = true;
      tmp = TextFieldController.getValideStringFormula(tmp, isUnsigned);
      poissonNb.setText(tmp);
      if (TextFieldController.isReadyToBeCalculated(tmp) && !poissonTime.getText().isEmpty() && tmp.length() > 0) {
        ScriptEngineManager mgr = new ScriptEngineManager();
        ScriptEngine engine = mgr.getEngineByName("JavaScript");
        try {
          tmp = engine.eval(tmp).toString();
        } catch (ScriptException e) {
          e.printStackTrace();
          return;
        }
        int nb;
        if (tmp.contains(".") || tmp.contains("\\.")) {
          double tt = Double.parseDouble(tmp);
          nb = (int) Math.round(tt);
        } else {
          nb = Integer.parseInt(tmp);
        }
        lbl10.setText(df.format(MmskController.poisson(mmskTable.getSelectionModel().selectedItemProperty().getValue(),
            Integer.parseInt(poissonTime.getText()), nb)));
      }
    } else {
      lbl10.setText("");
    }
  }

  private void updatePoissonTime(ObservableValue<? extends String> observable, String oldValue, String newValue,
      DecimalFormat df) {
    if (!poissonTime.getText().isEmpty() && mmskTable.getSelectionModel().getSelectedItem() != null) {
      String tmp = newValue;
      boolean isUnsigned = true;
      tmp = TextFieldController.getValideStringFormula(tmp, isUnsigned);
      poissonTime.setText(tmp);
      if (TextFieldController.isReadyToBeCalculated(tmp) && !poissonNb.getText().isEmpty() && tmp.length() > 0) {
        ScriptEngineManager mgr = new ScriptEngineManager();
        ScriptEngine engine = mgr.getEngineByName("JavaScript");
        try {
          tmp = engine.eval(tmp).toString();
        } catch (ScriptException e) {
          e.printStackTrace();
          return;
        }
        int nb;
        if (tmp.contains(".") || tmp.contains("\\.")) {
          double tt = Double.parseDouble(tmp);
          nb = (int) Math.round(tt);
        } else {
          nb = Integer.parseInt(tmp);
        }
        lbl10.setText(df.format(MmskController.poisson(mmskTable.getSelectionModel().selectedItemProperty().getValue(),
            nb, Integer.parseInt(poissonNb.getText()))));
      }
    } else {
      lbl10.setText("");
    }
  }

  private void updateProbaDansSysSup(ObservableValue<? extends String> observable, String oldValue, String newValue,
      DecimalFormat df) {
    if (!probaDansSysSup.getText().isEmpty() && mmskTable.getSelectionModel().getSelectedItem() != null) {
      String tmp = newValue;
      boolean isUnsigned = true;
      tmp = TextFieldController.getValideStringFormula(tmp, isUnsigned);
      probaDansSysSup.setText(tmp);
      if (TextFieldController.isReadyToBeCalculated(tmp) && tmp.length() > 0) {
        ScriptEngineManager mgr = new ScriptEngineManager();
        ScriptEngine engine = mgr.getEngineByName("JavaScript");
        try {
          tmp = engine.eval(tmp).toString();
        } catch (ScriptException e) {
          e.printStackTrace();
          return;
        }
        double nb = Double.parseDouble(tmp);
        lbl8.setText(df.format(
            MmskController.duree_sejour_systeme(mmskTable.getSelectionModel().selectedItemProperty().getValue(), nb)));
      }
    } else {
      lbl8.setText("");
    }
  }

  private void updateProbaSansService(ObservableValue<? extends String> observable, String oldValue, String newValue,
      DecimalFormat df) {
    if (!probaSansService.getText().isEmpty() && mmskTable.getSelectionModel().getSelectedItem() != null) {
      String tmp = newValue;
      boolean isUnsigned = true;
      tmp = TextFieldController.getValideStringFormula(tmp, isUnsigned);
      probaSansService.setText(tmp);
      if (TextFieldController.isReadyToBeCalculated(tmp) && tmp.length() > 0) {
        ScriptEngineManager mgr = new ScriptEngineManager();
        ScriptEngine engine = mgr.getEngineByName("JavaScript");
        try {
          tmp = engine.eval(tmp).toString();
        } catch (ScriptException e) {
          e.printStackTrace();
          return;
        }
        double nb = Double.parseDouble(tmp);
        lbl9.setText(df.format(MmskController
            .duree_sejour_sans_service(mmskTable.getSelectionModel().selectedItemProperty().getValue(), nb)));
      }
    } else {
      lbl9.setText("");
    }
  }

  private void updateQi(ObservableValue<? extends String> observable, String oldValue, String newValue,
      DecimalFormat df) {
    if (!qi.getText().isEmpty() && mmskTable.getSelectionModel().getSelectedItem() != null) {
      String tmp = newValue;
      boolean isUnsigned = true;
      tmp = TextFieldController.getValideStringFormula(tmp, isUnsigned);
      // set textField with the formula
      qi.setText(tmp);
      if (TextFieldController.isReadyToBeCalculated(tmp) && tmp.length() > 0) {
        ScriptEngineManager mgr = new ScriptEngineManager();
        ScriptEngine engine = mgr.getEngineByName("JavaScript");
        try {
          tmp = engine.eval(tmp).toString();
          // System.out.println("tmp=" + tmp);
        } catch (ScriptException e) {
          e.printStackTrace();
          return;
        }
        int nb;
        if (/* isAnInteger && */tmp.contains(".") || tmp.contains("\\.")) {
          // if isAnInteger and the result has a point
          // System.out.print("parse ");
          double tt = Double.parseDouble(tmp);
          nb = (int) Math.round(tt); // round to int and set color to orange
                                     // with texte au survol saying
          // "xxx.xx is not an integer, rounded to xxy"
          // System.out.println(tt + " into " + nb);
        } else {
          nb = Integer.parseInt(tmp);
        }
        lbl7.setText(df.format(MmskController.qj(mmskTable.getSelectionModel().selectedItemProperty().getValue(), nb)));
      }
    } else {
      lbl7.setText("");
    }
  }
}
