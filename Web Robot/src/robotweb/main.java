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

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;

/**
 * Classe main permettant d'executer le programme en mode ligne de commande
 *
 * @author hux
 */
public class main {

    public static volatile int nb_request = 0;
    public static volatile double debit_moyen = 0.0;
    public static volatile double temps_moyen = 0.0;

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {

        String url_base = "http://www.bedetheque.com/search/tout?";
        String url_rechTexte = "RechTexte=";
        String url_rechWhere = "&RechWhere=0";
        int nb_thread = 100;

        //26*26*26 = 17576
        int calc = 17576;

        ExecutorService executor = Executors.newFixedThreadPool(nb_thread);
        for (int i = 0; i < nb_thread; i++) {
            executor.execute(new Thread_url(i, calc, nb_thread, url_base, url_rechTexte, url_rechWhere));
        }

        executor.shutdown();
        try {
            Thread.sleep(6000);//dors pendant 6 seconde afin que les threads ce soit correctement lancé
            while (!executor.isTerminated()) {
                Thread.sleep(3000);//dors pendant 3 seconde si interrompu envoie une interruption exception
                System.out.println("nb requetes : " + nb_request + "\n débit moyen : " + debit_moyen + "\n temps moyen :" + temps_moyen);//affiche les valeurs au fure et à mesure

            }
        } catch (InterruptedException ie) {
            // (Re-)Cancel if current thread also interrupted
            executor.shutdownNow();
            // Preserve interrupt status
            Thread.currentThread().interrupt();
        }
        shutdownAndAwaitTermination(executor);//gére l'intéruption normalement
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
