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

/**
 *
 * @author hux
 */
public class RobotWebException extends Exception {

    private static final long serialVersionUID = 1L;

    /**
     * Constructs a new RobotWebException with the specified detail message as
     * to why the connect error occurred. A detail message is a String that
     * gives a specific description of this error.
     *
     * @param msg the detail message
     */
    public RobotWebException(String msg) {
        super(msg);
    }

    /**
     * Construct a new RobotWebException with no detailed message.
     */
    public RobotWebException() {
    }

}
