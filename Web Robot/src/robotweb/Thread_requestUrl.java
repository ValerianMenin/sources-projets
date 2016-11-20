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
 * Cette thread lance une requête à l'url passée en paramètre
 *
 * @author hux
 */
public class Thread_requestUrl implements Runnable {

    /**
     * Erreur
     */
    private String ERREUR_CLOSEDBYINTERRUPT_EXC = "Arrêt après interruption";
    private String ERREUR_ROBOTWEB_EXC = "Erreur du robotWeb";
    /**
     * Attribut
     */
    private int index_thread = 0; // numéro de la thread
    private final int nb_requetes_a_faire; //nombre de requete à faire
    private final int nb_thread; //nombre de thread lancé depuis la thread parent
    private final String url; //url à consulter
    private double debit_moyen_thread_old;
    private double temps_moyen_thread_old;
    private int nb_requetes_thread;

    /**
     * Constructeur de la classe
     *
     * @param index_thread
     * @param calc
     * @param nb_thread
     * @param url
     */
    public Thread_requestUrl(int index_thread, int calc, int nb_thread, String url) {
        this.index_thread = index_thread;
        this.nb_requetes_a_faire = calc;
        this.nb_thread = nb_thread;
        this.url = url;
        debit_moyen_thread_old = 0.0;
        nb_requetes_thread = 0;
        temps_moyen_thread_old = 0.0;
    }

    /**
     * Lance la thread : Execute le nombre de requete demandé sur l'url passé en
     * paramètre
     *
     */
    @Override
    public void run() {
        System.out.println("robotweb.Thread_requestUrl.run()");
        //calcul des bornes de requêtes à faire
        int begin = index_thread * (nb_requetes_a_faire / nb_thread);
        int end = (index_thread + 1) * (nb_requetes_a_faire / nb_thread);

        try {

            //ajout des tâches à la liste de tâches
            for (int i = begin; i < end; i++) {
                //lancement de la requête via le robotWeb
                RobotWeb robot = new RobotWeb(url, 30, index_thread);
                update_debit_moyen(robot);
            }

        } catch (ClosedByInterruptException e) {
            Logger.getLogger(Thread_requestUrl.class.getName()).log(Level.SEVERE, ERREUR_CLOSEDBYINTERRUPT_EXC);
        } catch (RobotWebException ex) {
            Logger.getLogger(Thread_requestUrl.class.getName()).log(Level.SEVERE, ERREUR_ROBOTWEB_EXC);
        }

    }

    private void update_debit_moyen(RobotWeb robot) {
        //calcul des temps et débit (synchronisé par variable volatile)

        windows.nb_request.incrementAndGet();
        nb_requetes_thread++;

        double debit_moyen_thread_new = ((debit_moyen_thread_old * (nb_requetes_thread - 1) + robot.getDebit()) / nb_requetes_thread);//calcul du débit moyen de la thread

        windows.debit_moyen_threads.compareAndSet(index_thread, Double.doubleToLongBits(debit_moyen_thread_old), Double.doubleToLongBits(debit_moyen_thread_new));

        debit_moyen_thread_old = debit_moyen_thread_new;

        double temps_moyen_thread_new = ((temps_moyen_thread_old * (nb_requetes_thread - 1) + robot.getTime()) / nb_requetes_thread);//calcul du débit moyen de la thread

        windows.temps_moyen_threads.compareAndSet(index_thread, Double.doubleToLongBits(temps_moyen_thread_old), Double.doubleToLongBits(temps_moyen_thread_new));

        temps_moyen_thread_old = debit_moyen_thread_new;
    }
}
