package polytech.tours.di.parallel.tsp;

import java.text.DecimalFormat;
/**
 * Provides a concrete implementation of a TSP instance
 * @author Jorge E. Mendoza (dev@jorge-mendoza.com)
 * @version %I%, %G%
 * @since Jan 8, 2015
 *
 */
public class Instance{
	/**
	 * The distance matrix
	 */
	private double[][] matrix;
	/**
	 * Constructs a new TSP instance
	 * @param n number of nodes in the underlying graph
	 */
	public Instance(int n){
		this.matrix=new double[n][n];
	}
	/**
	 * 
	 * @param i the first node
	 * @param j the second node
	 * @return the distance between node <code>i</code> and node <code>j</code>
	 */
	public double getDistance(int i, int j){
		return this.matrix[i][j];
	}
	/**
	 * Sets the distance between nodes <code>i</code> and <code>j</code> to <code>distance</code>
	 * @param i the first node
	 * @param j the second node
	 * @param distance the distance between node <code>i</code> and <code>j</code>
	 */
	public void set(int i, int j, double distance){
		this.matrix[i][j]=distance;
	}
	/**
	 * Sets the distance matrix
	 * @param matrix the distance matrix to set
	 */
	public void setDistanceMatrix(double[][] matrix) {
		this.matrix=matrix.clone();
	}
	/**
	 * 
	 * @return the number of nodes in the instance
	 */
	public int getN(){
		return matrix.length;
	}
	/**
	 * 
	 * @return a copy of the distance matrix
	 */
	public double[][] getDistanceMatrix(){
		return this.matrix.clone();
	}
	
	/**
	 * Prints the distance matrix to the standard output
	 * @param format decimal format (e.g., #.0000 for rounding to 4 decimals)
	 */
	public void printDistanceMatrix(String format){
		DecimalFormat df=new DecimalFormat(format);
		for(int i=0; i<this.matrix.length;i++){
			for(int j=0; j<this.matrix[0].length; j++){
				System.out.print(df.format(matrix[i][j])+"\t");
			}
			System.out.print("\n");
		}
		System.out.print("\n");
	}
	
}
