/*
 * Copyright (C) 2016 hux
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
package robotweb;

import java.nio.channels.ClosedByInterruptException;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author hux
 */
public class Thread_url implements Runnable {

    private String ERREUR_CLOSEDBYINTERRUPT_EXC = "Arrêt après interruption";
    private String ERREUR_ROBOTWEB_EXC = "Erreur du robotWeb";

    private int index_thread = 0;
    private int calc;
    private int nb_thread;
    private String url_base;
    private String url_rechTexte;
    private String url_rechWhere;

    public Thread_url(int index_thread, int calc, int nb_thread, String url_base, String url_rechTexte, String url_rechWhere) {
        this.index_thread = index_thread;
        this.calc = calc;
        this.nb_thread = nb_thread;
        this.url_base = url_base;
        this.url_rechWhere = url_rechWhere;
        this.url_rechTexte = url_rechTexte;
    }

    /**
     *
     *
     */
    @Override
    public void run() {
        String url_search = "";
        int begin = index_thread * (calc / nb_thread);
        int end = (index_thread + 1) * (calc / nb_thread);

        //ajout des tâches à la liste de tâches
        for (int i = begin; i < end; i++) {
            int val1 = (i / (26 * 26)) % 26;
            int val2 = (i / 26) % 26;
            int val3 = i % 26;

            String val_of_int1 = String.valueOf(Math.abs(val1));
            String val_of_int2 = String.valueOf(Math.abs(val2));
            String val_of_int3 = String.valueOf(Math.abs(val3));

            Character char1 = (char) (Integer.parseInt(val_of_int1) + 'a');
            Character char2 = (char) (Integer.parseInt(val_of_int2) + 'a');
            Character char3 = (char) (Integer.parseInt(val_of_int3) + 'a');

            url_search = url_base + url_rechTexte + char1 + char2 + char3 + url_rechWhere;

            RobotWeb robot;
            try {
                robot = new RobotWeb(url_search, 30, index_thread);

                //calcul des temps et débit (synchronisé par variable volatile)
                main.nb_request++;//increment la variable volatile
                main.debit_moyen = (main.debit_moyen * (main.nb_request - 1) + robot.getDebit()) / main.nb_request;//calcul du débit moyen
                main.temps_moyen = (main.temps_moyen * (main.nb_request - 1) + robot.getTime()) / main.nb_request;//calcul du temps moyen

            } catch (ClosedByInterruptException e) {
                Logger.getLogger(Thread_requestUrl.class.getName()).log(Level.SEVERE, ERREUR_CLOSEDBYINTERRUPT_EXC);
            } catch (RobotWebException ex) {
                Logger.getLogger(Thread_requestUrl.class.getName()).log(Level.SEVERE, ERREUR_ROBOTWEB_EXC);
            }

        }

    }

}
