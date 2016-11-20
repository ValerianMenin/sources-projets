package application.model;

import java.time.LocalTime;
import java.util.Calendar;

import application.controller.MmskController;
import javafx.beans.property.DoubleProperty;
import javafx.beans.property.IntegerProperty;
import javafx.beans.property.ObjectProperty;
import javafx.beans.property.SimpleDoubleProperty;
import javafx.beans.property.SimpleIntegerProperty;
import javafx.beans.property.SimpleObjectProperty;
import javafx.beans.property.SimpleStringProperty;
import javafx.beans.property.StringProperty;

/**
 * Model class for a Mmsk.
 *
 * @author MENIN Valerian
 */
public class Mmsk {
  private ObjectProperty<LocalTime> derniereMAJ;

  private DoubleProperty processusArrive;
  private DoubleProperty processusService;
  private IntegerProperty nombreService;
  private IntegerProperty borneSupClientSysteme;
  private IntegerProperty nbClientsPotentiel;
  private StringProperty reglePassage;

  private DoubleProperty ro;
  private DoubleProperty q0;
  private DoubleProperty l;
  private DoubleProperty lq;
  private DoubleProperty w;
  private DoubleProperty wq;

  /**
   * Default constructor.
   */
  public Mmsk() {
    // ==============================================
    this(null, null);
    // ==============================================
  }

  /**
   *
   * @param processusArrive
   * @param processusService
   * @param nombreService
   * @param borneSupClientSysteme
   * @param nbClientsPotentiel
   * @param reglePassage
   */
  public Mmsk(double processusArrive, double processusService, int nombreService, int borneSupClientSysteme,
      int nbClientsPotentiel, String reglePassage) {
    this.derniereMAJ = new SimpleObjectProperty<>(LocalTime.of(Calendar.getInstance().get(Calendar.HOUR_OF_DAY),
        Calendar.getInstance().get(Calendar.MINUTE), Calendar.getInstance().get(Calendar.SECOND)));
    this.processusArrive = new SimpleDoubleProperty(processusArrive);
    this.processusService = new SimpleDoubleProperty(processusService);
    this.nombreService = new SimpleIntegerProperty(nombreService);
    this.borneSupClientSysteme = new SimpleIntegerProperty(borneSupClientSysteme);
    this.nbClientsPotentiel = new SimpleIntegerProperty(nbClientsPotentiel);
    this.reglePassage = new SimpleStringProperty(reglePassage);

    // TODO appeler les fonctions qui calculent ro, q0, L, Lq, W et Wq
    // mmsk.setRo(MmskController.calcRo(mmsk));

    this.ro = new SimpleDoubleProperty(MmskController.calcRo(this));
    this.q0 = new SimpleDoubleProperty(0);
    this.l = new SimpleDoubleProperty(0);
    this.lq = new SimpleDoubleProperty(0);
    this.w = new SimpleDoubleProperty(0);
    this.wq = new SimpleDoubleProperty(0);

    // Initialize the 3 fields
  }

  /**
   * Constructor with some initial data.
   *
   * @param firstName
   * @param lastName
   */
  public Mmsk(String firstName, String lastName) {
    this.derniereMAJ = new SimpleObjectProperty<>(LocalTime.of(Calendar.getInstance().get(Calendar.HOUR_OF_DAY),
        Calendar.getInstance().get(Calendar.MINUTE), Calendar.getInstance().get(Calendar.SECOND)));
    this.processusArrive = new SimpleDoubleProperty(0);
    this.processusService = new SimpleDoubleProperty(0);
    this.nombreService = new SimpleIntegerProperty(1);
    this.borneSupClientSysteme = new SimpleIntegerProperty(-1);
    this.nbClientsPotentiel = new SimpleIntegerProperty(-1);
    this.reglePassage = new SimpleStringProperty("FIFO");

    this.ro = new SimpleDoubleProperty(0);
    this.q0 = new SimpleDoubleProperty(0);
    this.l = new SimpleDoubleProperty(0);
    this.lq = new SimpleDoubleProperty(0);
    this.w = new SimpleDoubleProperty(0);
    this.wq = new SimpleDoubleProperty(0);
  }

  /**
   * Gets the borne sup client systeme.
   *
   * @return void
   */
  public int getBorneSupClientSysteme() {
    return borneSupClientSysteme.get();
  }

  /**
   * Gets the borne sup client systeme property.
   *
   * @return the borne sup client systeme property
   */
  public IntegerProperty getBorneSupClientSystemeProperty() {
    return borneSupClientSysteme;
  }

  /**
   * Gets the derniere MAJ.
   *
   * @return the derniere MAJ
   */
  public LocalTime getDerniereMAJ() {
    return derniereMAJ.get();
  }

  /**
   * Gets the derniere MAJ property.
   *
   * @return the derniere MAJ property
   */
  public ObjectProperty<LocalTime> getDerniereMAJProperty() {
    return derniereMAJ;
  }

  /**
   * Gets the l.
   *
   * @return the l
   */
  public double getL() {
    return l.get();
  }

  /**
   * Gets the l property.
   *
   * @return the l property
   */
  public DoubleProperty getLProperty() {
    return l;
  }

  /**
   * Gets the lq.
   *
   * @return the lq
   */
  public double getLq() {
    return lq.get();
  }

  /**
   * Gets the lq property.
   *
   * @return the lq property
   */
  public DoubleProperty getLqProperty() {
    return lq;
  }

  /**
   * Gets the nb clients potentiel.
   *
   * @return the nb clients potentiel
   */
  public int getNbClientsPotentiel() {
    return nbClientsPotentiel.get();
  }

  /**
   * Gets the nb clients potentiel property.
   *
   * @return the nb clients potentiel property
   */
  public IntegerProperty getNbClientsPotentielProperty() {
    return nbClientsPotentiel;
  }

  /**
   * Gets the nombre service.
   *
   * @return the nombre service
   */
  public int getNombreService() {
    return nombreService.get();
  }

  /**
   * Gets the nombre service property.
   *
   * @return the nombre service property
   */
  public IntegerProperty getNombreServiceProperty() {
    return nombreService;
  }

  /**
   * Gets the processus arrive.
   *
   * @return the processus arrive
   */
  public double getProcessusArrive() {
    return processusArrive.get();
  }

  /**
   * Gets the processus arrive property.
   *
   * @return the processus arrive property
   */
  public DoubleProperty getProcessusArriveProperty() {
    return processusArrive;
  }

  /**
   * Gets the processus service.
   *
   * @return the processus service
   */
  public double getProcessusService() {
    return processusService.get();
  }

  /**
   * Gets the processus service property.
   *
   * @return the processus service property
   */
  public DoubleProperty getProcessusServiceProperty() {
    return processusService;
  }

  /**
   * Gets the q0.
   *
   * @return the q0
   */
  public double getQ0() {
    return q0.get();
  }

  /**
   * Gets the q 0 property.
   *
   * @return the q 0 property
   */
  public DoubleProperty getQ0Property() {
    return q0;
  }

  /**
   * Gets the regle passage.
   *
   * @return the regle passage
   */
  public String getReglePassage() {
    return reglePassage.get();
  }

  /**
   * Gets the regle passage property.
   *
   * @return the regle passage property
   */
  public StringProperty getReglePassageProperty() {
    return reglePassage;
  }

  /**
   * Gets the ro.
   *
   * @return the ro
   */
  public double getRo() {
    return ro.get();
  }

  /**
   * Gets the ro property.
   *
   * @return the ro property
   */
  public DoubleProperty getRoProperty() {
    return ro;
  }

  /**
   * Gets the w.
   *
   * @return the w
   */
  public double getW() {
    return w.get();
  }

  /**
   * Gets the w property.
   *
   * @return the w property
   */
  public DoubleProperty getWProperty() {
    return w;
  }

  /**
   * Gets the wq.
   *
   * @return the wq
   */
  public double getWq() {
    return wq.get();
  }

  /**
   * Gets the wq property.
   *
   * @return the wq property
   */
  public DoubleProperty getWqProperty() {
    return wq;
  }

  /**
   * Sets the borne sup client systeme.
   *
   * @param borneSupClientSysteme
   *          the new borne sup client systeme
   */
  public void setBorneSupClientSysteme(int borneSupClientSysteme) {
    this.borneSupClientSysteme.set(borneSupClientSysteme);
  }

  /**
   * Sets the derniere MAJ.
   *
   * @param derniereMAJ
   *          the new derniere MAJ
   */
  public void setDerniereMAJ(LocalTime derniereMAJ) {
    this.derniereMAJ.set(derniereMAJ);
  }

  /**
   * Sets the l.
   *
   * @param l
   *          the new l
   */
  public void setL(double l) {
    this.l.set(l);
  }

  /**
   * Sets the lq.
   *
   * @param lq
   *          the new lq
   */
  public void setLq(double lq) {
    this.lq.set(lq);
  }

  /**
   * Sets the nb clients potentiel.
   *
   * @param nbClientsPotentiel
   *          the new nb clients potentiel
   */
  public void setNbClientsPotentiel(int nbClientsPotentiel) {
    this.nbClientsPotentiel.set(nbClientsPotentiel);
  }

  /**
   * Sets the nombre service.
   *
   * @param nombreService
   *          the new nombre service
   */
  public void setNombreService(int nombreService) {
    this.nombreService.set(nombreService);
  }

  /**
   * Sets the processus arrive.
   *
   * @param processusArrive
   *          the new processus arrive
   */
  public void setProcessusArrive(double processusArrive) {
    this.processusArrive.set(processusArrive);
  }

  /**
   * Sets the processus service.
   *
   * @param processusService
   *          the new processus service
   */
  public void setProcessusService(double processusService) {
    this.processusService.set(processusService);
  }

  /**
   * Sets the q0.
   *
   * @param q0
   *          the new q0
   */
  public void setQ0(double q0) {
    this.q0.set(q0);
  }

  /**
   * Sets the regle passage.
   *
   * @param reglePassage
   *          the new regle passage
   */
  public void setReglePassage(String reglePassage) {
    this.reglePassage.set(reglePassage);
  }

  /**
   * Sets the ro.
   *
   * @param ro
   *          the new ro
   */
  public void setRo(double ro) {
    this.ro.set(ro);
  }

  /**
   * Sets the w.
   *
   * @param w
   *          the new w
   */
  public void setW(double w) {
    this.w.set(w);
  }

  /**
   * Sets the wq.
   *
   * @param wq
   *          the new wq
   */
  public void setWq(double wq) {
    this.wq.set(wq);
  }
}
