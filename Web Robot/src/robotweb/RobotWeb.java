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

import java.io.BufferedOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.ConnectException;
import java.net.MalformedURLException;
import java.net.NoRouteToHostException;
import java.net.SocketException;
import java.net.URL;
import java.nio.channels.ClosedByInterruptException;
import java.nio.file.*;
import static java.nio.file.StandardOpenOption.*;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.net.ssl.HttpsURLConnection;

/**
 * Classe qui permet de créer un objet robot qui permet de lancer une requête
 * vers une url et de récupérer la page web
 *
 * @author hux
 */
public class RobotWeb {

    /**
     * Erreur
     */
    private String ERREUR_TIMEOUTCONNECT_EXC = "Erreur Timeout connect exception";
    private String ERREUR_ACCESSPATH_EXC = "Aucun chemin d'accès vers le serveur";
    private String ERREUR_SOCKET_EXC = "Attention erreur Socket";
    private String ERREUR_INPUTSTREAM_EXC = "Attention input stream erreur";

    /**
     * Attribute
     */
    private java.net.URL url;
    private String research;
    private byte[] array;
    private InputStream iS;
    private double debit;
    private double time;

    /**
     *
     * @param ad
     * @param buffer
     * @param index_thread
     * @throws java.nio.channels.ClosedByInterruptException
     * @throws robotweb.RobotWebException
     */
    public RobotWeb(String ad, int buffer, int index_thread) throws ClosedByInterruptException, RobotWebException {
        long start_time = 0;
        long end_time = 0;
        try {
            boolean isHttpsRequest = ad.contains("https");
            HttpsURLConnection con = null;
            if (isHttpsRequest) {
                url = new URL(ad);
                con = (HttpsURLConnection) url.openConnection();
            } else {
                url = new URL(ad);
            }

            array = new byte[buffer];
            research = ad;
            start_time = System.nanoTime();
            try {
                if (isHttpsRequest) {
                    iS = con.getInputStream();
                } else {
                    iS = url.openStream();
                }
                end_time = System.nanoTime();
                debit = toMbs(trace(index_thread), (end_time - start_time));
                time = toS(end_time - start_time);
            } catch (ConnectException ex) {
                Logger.getLogger(RobotWeb.class.getName()).log(Level.SEVERE, ERREUR_TIMEOUTCONNECT_EXC);
                throw new RobotWebException(ERREUR_TIMEOUTCONNECT_EXC);
            } catch (NoRouteToHostException ex) {
                Logger.getLogger(RobotWeb.class.getName()).log(Level.SEVERE, ERREUR_ACCESSPATH_EXC);
                throw new RobotWebException(ERREUR_ACCESSPATH_EXC);
            } catch (SocketException ex) {
                Logger.getLogger(RobotWeb.class.getName()).log(Level.SEVERE, ERREUR_SOCKET_EXC, ex);
                throw new RobotWebException(ERREUR_SOCKET_EXC);
            } catch (IOException ex) {
                Logger.getLogger(RobotWeb.class.getName()).log(Level.SEVERE, ERREUR_INPUTSTREAM_EXC, ex);
                throw new RobotWebException(ERREUR_INPUTSTREAM_EXC);
            }
        } catch (MalformedURLException ex) {
            Logger.getLogger(RobotWeb.class.getName()).log(Level.SEVERE, "Attention erreur lors de l'affectation de l'url.", ex);
        } catch (IOException ex) {
            Logger.getLogger(RobotWeb.class.getName()).log(Level.SEVERE, "IOEXception url", ex);
        }

    }

    /**
     *
     * @return
     */
    public double getTime() {
        return time;
    }

    /**
     *
     * @return
     */
    public double getDebit() {
        return debit;
    }

    /**
     *
     *
     * @param index_thread
     * @return
     */
    protected long trace(int index_thread) throws ClosedByInterruptException, RobotWebException {
        Path file_path = null;
        if (research != null) {
            //int index_egal = research.indexOf("=");
            //file_path = Paths.get("/home/hux/NetBeansProjects/WebRobot/file/fileN" + research.substring(index_egal + 1, index_egal + 4));
            file_path = Paths.get("/home/hux/NetBeansProjects/WebRobot/file/fileN" + index_thread);
        }

        long size_page = 0;

        if (file_path != null) {
            int size = 0;
            try {
                OutputStream out = new BufferedOutputStream(Files.newOutputStream(file_path, CREATE, APPEND));
                do {
                    if (iS != null) {
                        size = iS.read(array);
                        size_page += size;
                        out.write(array, 0, array.length);
                    }
                } while (size != -1);
                iS.close();
            } catch (IOException ex) {
                Logger.getLogger(RobotWeb.class.getName()).log(Level.SEVERE, null, ex);
                throw new RobotWebException("Erreur IOException");
            }
        }
        return size_page;
    }

    /**
     * From byte / ns to Mbits.s.
     *
     * @param tsize
     * @param dt
     * @return
     */
    protected double toMbs(long tsize, long dt) {
        return toMb(tsize) / toS(dt);
    }

    /**
     * From byte to Mbyte.
     *
     * @param tsize
     * @return
     */
    protected double toMb(long tsize) {
        return ((double) tsize * 8) / (1024 * 1024);
    }

    /**
     * From nano seconds to seconds.
     *
     * @param dt
     * @return
     */
    protected double toS(long dt) {
        return ((double) dt) / 1000000000;
    }

    /**
     * Tu subsitutute a dot '.' with a comma ',' at t he printing level.
     *
     * @param value
     * @return
     */
    protected static String wC(double value) {
        return Double.toString(value).replace('.', ',');
    }

}
