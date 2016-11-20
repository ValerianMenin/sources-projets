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

import java.awt.Graphics;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;
import static robotweb.windows.jTxtPane_graphe;
import static robotweb.windows.nb_request;

/**
 * Cette classe permet de créer une thread qui va modifier le contenu de la
 * fenetre du programme Elle execute le nombre de thread demandé et répartie le
 * nombre de requetes à faire sur les threads Elle affiche ensuite le temps
 * moyen et le débit moyen de chaque requête
 *
 * @author hux
 */
public class thread_print_graphique implements Runnable {

    private final int nb_requete_a_faire;
    private final int nb_tasks;
    private final String url;

    public thread_print_graphique(int nb_requete_a_faire, int nb_tasks, String url) {
        this.nb_requete_a_faire = nb_requete_a_faire;
        this.nb_tasks = nb_tasks;
        this.url = url;
        windows.nb_request.getAndSet(0);
    }

    @Override
    public void run() {

        int nb_threads = Runtime.getRuntime().availableProcessors();
        System.out.println("nb processeurs :" + nb_threads);
        //l'executor est déjà fait dans le windows.java il peut être partager
        ExecutorService executor = Executors.newFixedThreadPool(nb_threads);
        for (int i = 0; i < nb_tasks; i++) {
            executor.submit(new Thread_requestUrl(i, nb_requete_a_faire, nb_tasks, url));
        }

        windows.executor.shutdown();
        try {

            int temps = 0;
            int temps2 = 10;
            double debit_moyen_prec = 0.0;
            Thread.sleep(3000);//dors pendant 6 seconde afin que les threads ce soit correctement lancé
            while (!windows.executor.isTerminated()) {

                Thread.sleep(3000);//dors pendant 3 seconde si interrompu envoie une interruption exception
                double debit_moyen_courant = 0.0;
                double temps_moyen = 0.0;
                int index_thread = 0;

                while (index_thread < nb_tasks) {
                    temps_moyen += Double.longBitsToDouble(windows.temps_moyen_threads.get(index_thread));
                    index_thread++;
                }

                temps_moyen /= nb_tasks;

                index_thread = 0;

                while (index_thread < nb_tasks) {
                    debit_moyen_courant += Double.longBitsToDouble(windows.debit_moyen_threads.get(index_thread));
                    index_thread++;
                }

                debit_moyen_courant /= nb_tasks;

                //affichage de texte dans la console
                //affiche les valeurs au fure et_base, url_rechTexte, url_rechWhere à mesure
                String previous_text_console = windows.jTxtPaneConsole.getText();
                windows.jTxtPaneConsole.setText(previous_text_console + "\n nb requetes : " + windows.nb_request.get() + "\n débit moyen : " + debit_moyen_courant + "\n temps moyen :" + temps_moyen);

                Graphics g = windows.jTxtPane_graphe.getGraphics();
                //récupère la taille du JtextPane
                int height = windows.jTxtPane_graphe.getHeight();
                int width = jTxtPane_graphe.getWidth();

                //choix d'un intervalle pour les traits horizontaux
                int intervalle = height / 10;
                //traçage des lignes de fond
                if (g != null) {
                    g.drawLine(0, intervalle, width, intervalle);
                    g.drawLine(0, intervalle * 2, width, intervalle * 2);
                    g.drawLine(0, intervalle * 3, width, intervalle * 3);
                    g.drawLine(0, intervalle * 4, width, intervalle * 4);
                    g.drawLine(0, intervalle * 5, width, intervalle * 5);
                    g.drawLine(0, intervalle * 6, width, intervalle * 6);
                    g.drawLine(0, intervalle * 7, width, intervalle * 7);
                    g.drawLine(0, intervalle * 8, width, intervalle * 8);
                    g.drawLine(0, intervalle * 9, width, intervalle * 9);
                    //traçage de la ligne
                    g.drawLine(temps, height - ((int) (debit_moyen_prec * 100)), temps + temps2, height - ((int) (debit_moyen_courant * 100)));
                    debit_moyen_prec = debit_moyen_courant;//sauvegarde de l'ancien debit moyen
                    g.dispose();//affichage
                }
                temps += temps2;//mise à jour du temps

                windows.progressBar.setValue(nb_request.get());
                windows.progressBar.setToolTipText("Progression : " + nb_request);

            }
        } catch (InterruptedException ie) {
            // (Re-)Cancel if current thread also interrupted
            windows.executor.shutdownNow();
            // Preserve interrupt status
            Thread.currentThread().interrupt();
        }
        shutdownAndAwaitTermination(windows.executor);//gére l'intéruption normalement
    }

    /**
     *
     * @param pool
     */
    public static void shutdownAndAwaitTermination(ExecutorService pool) {
        //pool.shutdown(); // Disable new tasks from being submitted
        try {
            // Wait a while for existing tasks to terminate
            if (!pool.awaitTermination(1200, TimeUnit.SECONDS)) {
                pool.shutdownNow(); // Cancel currently executing tasks
                // Wait a while for tasks to respond to being cancelled
                if (!pool.awaitTermination(1200, TimeUnit.SECONDS)) {
                    System.err.println("Pool did not terminate");
                }
            }
        } catch (InterruptedException ie) {
            // (Re-)Cancel if current thread also interrupted
            pool.shutdownNow();
            // Preserve interrupt status
            Thread.currentThread().interrupt();
        }
    }

}
