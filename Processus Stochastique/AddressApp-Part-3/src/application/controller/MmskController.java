package application.controller;

import application.model.Mmsk;

/**
 * @author MENIN Valerian
 *
 */
public class MmskController {

  private static double calcQ0(Mmsk mmsk) {
    int k = mmsk.getBorneSupClientSysteme();
    int serv = mmsk.getNombreService();
    double ro = mmsk.getRo();

    double result = 0;
    double sum = 0; // M|M|1

    if (k < 0) {
      if (serv > 1) { // M|M|S
        for (int j = 0; j <= serv - 1; j++) {
          sum += Math.pow(ro * serv, j) / factoriel(j);
        }
      }

      result = 1 / (sum + Math.pow((ro * serv), serv) / (factoriel(serv) * (1 - ro)));
      return result;
    } else {
      if (ro == 1) {
        return 1 / k + 1;
      }
      if (ro != 1) {
        return (1 - ro) / (1 - Math.pow(ro, k + 1));
      }
      return result;
    }
  }

  /**
   * Calc ro.
   *
   * @param mmsk
   *          the mmsk
   * @return the double
   */
  public static double calcRo(Mmsk mmsk) {
    return mmsk.getProcessusArrive() / (mmsk.getNombreService() * mmsk.getProcessusService());
  }

  /**
   * Duree sejour sans service.
   *
   * @param mmsk
   *          the mmsk
   * @param temps
   *          the temps
   * @return the double
   */
  public static double duree_sejour_sans_service(Mmsk mmsk, double temps) {
    double result;
    int serv = mmsk.getNombreService();
    double qBase = mmsk.getQ0();
    double ro = mmsk.getRo();
    double mu = mmsk.getProcessusService();
    double psup0 = (Math.pow((ro * serv), 2)) / (factoriel(serv) * (1 - ro)) * qBase;

    result = Math.exp(-serv * mu * temps * (1 - ro)) * psup0;
    return result;

  }

  /**
   * Duree sejour systeme.
   *
   * @param mmsk
   *          the mmsk
   * @param temps
   *          the temps
   * @return the double
   */
  public static double duree_sejour_systeme(Mmsk mmsk, double temps) {
    double result;
    int serv = mmsk.getNombreService();
    double qBase = mmsk.getQ0();
    double ro = mmsk.getRo();
    double mu = mmsk.getProcessusService();
    if (serv == 1) {
      qBase = (1 - ro);
    }
    result = Math.exp(-mu * temps) * (1 + ((qBase * Math.pow((ro * serv), serv)) / (factoriel(serv) * (1 - ro)))
        * ((1 - Math.exp(-mu * temps * (serv - 1 - ro * serv))) / (serv - 1 - ro * serv)));
    return result;
  }

  /**
   * Factoriel.
   *
   * @param n
   *          the n
   * @return the double
   */
  public static double factoriel(double n) {
    if (n <= 1) {
      return 1;
    } else {
      return n * factoriel(n - 1);
    }
  }

  /**
   * Poisson.
   *
   * @param mmsk
   *          the mmsk
   * @param temps
   *          the temps
   * @param n
   *          the n
   * @return the double
   */
  public static double poisson(Mmsk mmsk, double temps, double n) {

    double result = (Math.pow((mmsk.getProcessusArrive() * temps), n)) / (factoriel(n))
        * Math.exp(-mmsk.getProcessusArrive() * temps);

    if (result < 0 || result > 1) {
      result = 0;
    }
    return result;
  }

  /**
   * Qj.
   *
   * @param mmsk
   *          the mmsk
   * @param j
   *          the j
   * @return the double
   */
  public static double qj(Mmsk mmsk, int j) {
    double result = 0;
    double ro = mmsk.getRo();
    int serv = mmsk.getNombreService();
    int k = mmsk.getBorneSupClientSysteme();

    if (k < 0) {
      if (0 <= j && j < serv) {
        result = Math.pow((ro * serv), j) / factoriel(j) * mmsk.getQ0();
        return result;
      } else if (j >= serv) {
        result = Math.pow(ro, j) * Math.pow(serv, j) / factoriel(serv) * mmsk.getQ0();
        return result;
      } else {
        return -1;
      }
    } else {
      if (ro == 1) {
        return 1 / k + 1;
      }
      if (ro != 1) {
        return ((1 - ro) * Math.pow(ro, j)) / (1 - Math.pow(ro, k + 1));
      }
      return result;
    }
  }

  /**
   * Update calc value.
   *
   * @param mmsk
   *          the mmsk
   */
  public static void updateCalcValue(Mmsk mmsk) {
    mmsk.setRo(calcRo(mmsk));
    mmsk.setQ0(calcQ0(mmsk));

    double ro = mmsk.getRo();
    int serv = mmsk.getNombreService();
    double qInit = mmsk.getQ0();
    int k = mmsk.getBorneSupClientSysteme();
    double lambda = mmsk.getProcessusArrive();

    double Lq = 0;
    double Wq = 0;
    double W = 0;
    double L = 0;

    if (k < 0) {
      Lq = (Math.pow((ro * serv), 2) * ro) / (factoriel(serv) * Math.pow((1 - ro), 2)) * qInit;

      Wq = Lq / lambda;

      W = Wq + 1 / mmsk.getProcessusService();
      L = lambda * W;
    }

    else {
      if (ro == 1) {
        L = k / 2;
      }
      if (ro != 1) {
        L = (ro * (1 - (k + 1) * Math.pow(ro, k) + k * Math.pow(ro, k + 1))) / ((1 - ro) * (1 - Math.pow(ro, k + 1)));
        Lq = L - (1 - qInit);
      }
    }
    mmsk.setLq(Lq);
    mmsk.setWq(Wq);
    mmsk.setW(W);
    mmsk.setL(L);
  }
}
