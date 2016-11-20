package atomicDouble;


import java.util.concurrent.atomic.AtomicReference;
import java.util.function.UnaryOperator;

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
public class AtomicDouble<Double> {

    private final AtomicReference<Double> ref;

    public AtomicDouble(Double ref) {
        this.ref = new AtomicReference<>(ref);
    }

    /**
     * Dereference current Atom. Will return a current value of the Atom.
     *
     * @return
     */
    public Double deref() {
        return ref.get();
    }

    /**
     * Apply an Operation that will atomically update the Atom.
     *
     * @param swapOp
     * @return
     */
    public Double swap(UnaryOperator<Double> swapOp) {
        for (;;) {                                  // (5)
            Double old = ref.get();                 // (1)
            Double newv = swapOp.apply(old);        // (2)
            if (ref.compareAndSet(old, newv)) {     // (3)
                return newv;                        // (4)
            }
        }
    }
}
