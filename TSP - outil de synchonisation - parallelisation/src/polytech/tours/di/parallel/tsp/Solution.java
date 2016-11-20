package polytech.tours.di.parallel.tsp;

import java.util.ArrayList;


/**
 * Concrete implementation of a solution represented by a single permutation of integers. This permutation becomes handy to represent
 * solutions to problems such as the traveling salesman problem, the knapsack problem, the flow shop scheduling problem, etc.
 * 
 * This concrete implementation is supported on an {@link ArrayList}.
 * 
 * @author Jorge E. Mendoza (dev@jorge-mendoza.com)
 * @version %I%, %G%
 * @since Jan 7, 2015
 *
 */
public class Solution extends ArrayList<Integer> implements Cloneable{
	
	/**
	 * Default serial version UID
	 */
	private static final long serialVersionUID = 1L;
	
	/**
	 * The objective function
	 */
	protected double of=Double.NaN;
	
	@Override
	public Solution clone() {
		Solution clone=new Solution();
		clone.of=this.of;
		for(Integer i:this){
			clone.add(i);
		}
		return clone;
	}

	
	public double getOF() {
		return this.of;
	}

	
	public void setOF(double of) {
		this.of=of;		
	}
	
	@Override
	public String toString(){
		String str=super.toString();
		str=str.concat("\t OF="+this.of);
		return str;
	}
	
	@Override
	public void add(int index, Integer element){
		if(index==this.size())
			super.add(element);
		else
			super.add(index,element);
	}
	/**
	 * Relocates the element in position <code>i</code> at position <code>j</code>. The method only manipulates the
	 * permutation it does not updates the objective function or any other attribute of the encoded solution.
	 * @param i the extracting position
	 * @param j the inserting position
	 */
	public void relocate(int i, int j){
		if(i<j){
			this.add(j,this.get(i));
			this.remove(i);
		}else{
			this.add(j,this.remove(i));
		}
	}
	
	/**
	 * Swaps the element in position <code>i</code> and the element in position <code>j</code>. The method
	 * only manipulates the permutation; it does not up update the objective function or any other attribute of the encode solution.
	 * Client classes are responsible to update the attributes of the solution.
	 * @param i the first swapping position. 0 <= i< {@link #size()}
	 * @param j the second swapping position. 0 <= j< {@link #size()}
	 */
	public void swap(int i, int j){
		int temp=this.get(i);
		this.set(i,this.get(j));
		this.set(j, temp);
	}
	
	/**
	 * 2opt the element in position <code>i</code> and the element in position <code>j</code>. The method
	 * only manipulates the permutation; it does not up update the objective function or any other attribute of the encode solution.
	 * Client classes are responsible to update the attributes of the solution.
	 * @param i the first 2opt position. 0 <= i< {@link #size()}
	 * @param j the second 2opt position. 0 <= j< {@link #size()}
	 */
	/*public void twoOpt(int i, int j){
		int lastNodeToSwap = (i+j)/2;
		//int indice=0;
		//System.out.println("[i, j, lastSwap]=["+i+", "+j+", "+lastNodeToSwap+"]");
		while(i<lastNodeToSwap){
			//System.out.println(i+" "+this);
			swap(++i, j--);
		}
	}*/
}
