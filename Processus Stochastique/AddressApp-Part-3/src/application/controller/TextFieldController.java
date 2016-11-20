/*
 * MENIN Valerian
 */
package application.controller;

import javax.script.ScriptEngine;
import javax.script.ScriptEngineManager;
import javax.script.ScriptException;

/**
 * The Class TextFieldController.
 *
 * @author MENIN Valerian
 */
public class TextFieldController {

  /**
   * Gets the calc.
   *
   * @param string
   *          the tmp
   * @return the calc
   */
  public static String getCalc(String string) {
    String tmp = string;
    ScriptEngineManager mgr = new ScriptEngineManager();
    ScriptEngine engine = mgr.getEngineByName("JavaScript");
    try {
      tmp = engine.eval(tmp).toString();
      // System.out.println("tmp=" + tmp);
    } catch (ScriptException e) {
      e.printStackTrace();
      return "0";
    }

    return tmp;
  }

  /**
   * Gets the valide string formula.
   *
   * @param newValue
   *          the new value
   * @param isUnsigned
   *          the is unsigned
   * @return the valide string formula
   */
  public static String getValideStringFormula(String newValue, boolean isUnsigned) {
    String valideStringFormula = newValue;
    valideStringFormula = valideStringFormula.replaceAll("[^0-9.+-/()\\*]", "");

    valideStringFormula = valideStringFormula.replaceAll("\\+\\+", "+");
    valideStringFormula = valideStringFormula.replaceAll("\\-\\-", "-");
    valideStringFormula = valideStringFormula.replaceAll("\\*\\*", "*");
    valideStringFormula = valideStringFormula.replaceAll("\\/\\/", "/");
    valideStringFormula = valideStringFormula.replaceAll("\\.\\.", ".");

    valideStringFormula = valideStringFormula.replaceAll("\\(\\)", "(");
    valideStringFormula = valideStringFormula.replaceAll("\\(\\*", "(");
    valideStringFormula = valideStringFormula.replaceAll("\\(\\/", "(");
    valideStringFormula = valideStringFormula.replaceAll("\\*\\)", "*");
    valideStringFormula = valideStringFormula.replaceAll("\\/\\)", "/");
    valideStringFormula = valideStringFormula.replaceAll("\\+\\)", "+");
    valideStringFormula = valideStringFormula.replaceAll("\\-\\)", "-");
    valideStringFormula = valideStringFormula.replaceAll("\\*\\*", "*");
    valideStringFormula = valideStringFormula.replaceAll("\\*\\/", "*");
    valideStringFormula = valideStringFormula.replaceAll("\\/\\/", "/");
    valideStringFormula = valideStringFormula.replaceAll("\\/\\*", "/");

    if (isUnsigned && valideStringFormula.startsWith("-")) {
      valideStringFormula = valideStringFormula.replaceFirst("-", "");
    }
    return valideStringFormula;
  }

  /**
   * Checks if is ready to be calculated.
   *
   * @param newValue
   *          the new value
   * @return true, if is ready to be calculated
   */
  public static boolean isReadyToBeCalculated(String newValue) {
    if (!(newValue.startsWith("+") && newValue.length() == 1) && !newValue.endsWith("+")) {
      if (!(newValue.startsWith("-") && newValue.length() == 1) && !newValue.endsWith("-")) {
        if (!newValue.startsWith(".") && !newValue.endsWith(".")) {
          if (!newValue.startsWith("/") && !newValue.endsWith("/")) {
            if (!newValue.startsWith("*") && !newValue.endsWith("*")) {
              if (newValue.replaceAll("\\(", "").length() == newValue.replaceAll("\\)", "").length()) {
                // System.out.println("isReadyToBeCalculated");
                return true;
              }
            }
          }
        }
      }
    }
    return false;
  }

}
