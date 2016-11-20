package polytech.tours.di.parallel.tsp;

import java.util.ArrayList;

/**
 * Computes the cost of a TSP solution
 * @author Jorge E. Mendoza (dev@jorge-mendoza.com)
 * @version %I%, %G%
 * @since Jan 9, 2015
 *
 */
public class TSPCostCalculator{
	
	private ArrayList<Integer> s;
	private double[][] distMatrix;
	
	/**
	 * @throws ClassCastException if <code>instance</code> cannot be casted to an instance of {@link TSPInstance} 
	 * or <code>s</code> cannot be casted to an instance of {@link Permutation} 
	 */
	public double calcOF(Instance instance, Solution s) throws ClassCastException {
		distMatrix=instance.getDistanceMatrix();
		this.s=s;//TSPCostCalculator.s=s;
		return calc();
	}
	/**
	 * static access to the calculator
	 * @param matrix the distance matrix
	 * @param s the TSP solution (permutation)
	 * @return the cost of <code>s</code>
	 */
	public double calcOF(double[][] matrix, ArrayList<Integer> s){
		distMatrix=matrix;
		this.s=s;//TSPCostCalculator.s=s;
		return calc();
	}
	/**
	 * internal implementation of the calculator
	 * @return the cost of a TSP solution
	 */
	private double calc(){
		double cost=0;
		for(int i=1;i<s.size();i++){
			cost=cost+distMatrix[s.get(i-1)][s.get(i)];
		}
		cost=cost+distMatrix[s.get(s.size()-1)][s.get(0)];
		return cost;
	}
	
	/**
	 * 
	 * @param i index of the fisrt node
	 * @param j index of the second node
	 * @param s the solution
	 * @return deltaOF : if <0 it means this is a better solution
	 */
	public double relocateOf(int i, int j, Solution s)
	{
		int nbOfNodes = s.size();
		if((i==nbOfNodes-1 && j==0) || i+1==j || i==j)
			return 0;
		
		int node_i         = s.get(i);
		int previousNode_i = s.get((i-1+nbOfNodes)%nbOfNodes);
		int nextNode_i 	   = s.get((i+1+nbOfNodes)%nbOfNodes);
		int node_j         = s.get(j);
		int previousNode_j = s.get((j-1+nbOfNodes)%nbOfNodes);
		
		/*double delta = -distMatrix[node_i][previousNode_i]-distMatrix[node_i][nextNode_i]+distMatrix[previousNode_i][nextNode_i]
				-distMatrix[previousNode_j][node_j]+distMatrix[node_i][previousNode_j]+distMatrix[node_i][node_j];

		if(delta<0)
		System.out.println(s+"\n[i, j], [i-1, i, i+1], [j-1, j, j+1]="
			+ "["+i+", "+j+"], ["+previousNode_i+", "+node_i+", "+nextNode_i+"], ["+previousNode_j+", "+node_j+", "+nextNode_j+"]"
					+"\n-distMatrix[node_i][previousNode_i]="+-distMatrix[node_i][previousNode_i]
					+"\n-distMatrix[node_i][nextNode_i]    ="+-distMatrix[node_i][nextNode_i]
					+"\n+distMatrix[node_i][previousNode_j]="+distMatrix[node_i][previousNode_j]
					+"\n+distMatrix[node_i][nextNode_j]    ="+distMatrix[node_i][nextNode_j]
					+"\n-distMatrix[node_j][previousNode_j]="+-distMatrix[node_j][previousNode_j]
					+"\n-distMatrix[node_j][nextNode_j]    ="+-distMatrix[node_j][nextNode_j]
					+"\n+distMatrix[node_j][previousNode_i]="+distMatrix[node_j][previousNode_i]
					+"\n+distMatrix[node_j][nextNode_i]    ="+distMatrix[node_j][nextNode_i]
					+"\n                              delta="+delta);*/
		return  -distMatrix[node_i][previousNode_i]-distMatrix[node_i][nextNode_i]+distMatrix[previousNode_i][nextNode_i]
					-distMatrix[previousNode_j][node_j]+distMatrix[node_i][previousNode_j]+distMatrix[node_i][node_j];//delta;
	}
	/**
	 * calcOf with a swap (don't do the swap)
	 * @param i // first swaping position
	 * @param j // second swaping position
	 * @param s the solution
	 * @return deltaOF : if <0 it means this is a better solution
	 */
	public double swapOf(int i, int j, Solution s)
	{
		int nbOfNodes = s.size();
		
		int node_i = s.get(i);
		int previousNode_i = s.get((i-1+nbOfNodes)%nbOfNodes);
		int nextNode_i 	   = s.get((i+1+nbOfNodes)%nbOfNodes);
		int node_j = s.get(j);
		int previousNode_j = s.get((j-1+nbOfNodes)%nbOfNodes);
		int nextNode_j 	   = s.get(Math.abs(j+1+nbOfNodes)%nbOfNodes);
		
		double delta = -distMatrix[node_i][previousNode_i]-distMatrix[node_i][nextNode_i]+distMatrix[node_i][previousNode_j]+distMatrix[node_i][nextNode_j]
				-distMatrix[node_j][previousNode_j]-distMatrix[node_j][nextNode_j]+distMatrix[node_j][previousNode_i]+distMatrix[node_j][nextNode_i];

		if(Math.abs(i-j)==1 || (i==0 && j==nbOfNodes-1))
			return delta + 2*distMatrix[node_i][node_j];
		
		/*System.out.println("[i, j], [i-1, i, i+1], [j-1, j, j+1]="
			+ "["+i+", "+j+"], ["+previousNode_i+", "+node_i+", "+nextNode_i+"], ["+previousNode_j+", "+node_j+", "+nextNode_j+"]"
					+"\n-distMatrix[node_i][previousNode_i]="+-distMatrix[node_i][previousNode_i]
					+"\n-distMatrix[node_i][nextNode_i]    ="+-distMatrix[node_i][nextNode_i]
					+"\n+distMatrix[node_i][previousNode_j]="+distMatrix[node_i][previousNode_j]
					+"\n+distMatrix[node_i][nextNode_j]    ="+distMatrix[node_i][nextNode_j]
					+"\n-distMatrix[node_j][previousNode_j]="+-distMatrix[node_j][previousNode_j]
					+"\n-distMatrix[node_j][nextNode_j]    ="+-distMatrix[node_j][nextNode_j]
					+"\n+distMatrix[node_j][previousNode_i]="+distMatrix[node_j][previousNode_i]
					+"\n+distMatrix[node_j][nextNode_i]    ="+distMatrix[node_j][nextNode_i]
					+"\n                              delta="+delta);*/
		return delta;
	}
	/**
	 * 
	 * @param i index of the fisrt node
	 * @param j index of the second node
	 * @param s the solution
	 * @return deltaOF : if <0 it means this is a better solution
	 */
	public double twoOptOf(int i, int j, Solution s)
	{
		int nbOfNodes = s.size();
		
		int node_i 		= s.get(i);
		int nextNode_i  = s.get((i+1+nbOfNodes)%nbOfNodes);
		int node_j      = s.get(j);
		int nextNode_j  = s.get((j+1+nbOfNodes)%nbOfNodes);
		
		/*double delta = -distMatrix[node_i][nextNode_i]-distMatrix[node_j][nextNode_j]
				+distMatrix[node_i][node_j]+distMatrix[nextNode_i][nextNode_j];
		//if(delta<0)
		System.out.println(s
			+"\n[i, j], [i, i+1, j, j+1]=["+i+", "+j+"], ["+node_i+", "+nextNode_i+", "+node_j+", "+nextNode_j+"]"+"\tdelta="+delta);*/
		
		return  -distMatrix[node_i][nextNode_i]-distMatrix[node_j][nextNode_j]
				+distMatrix[node_i][node_j]+distMatrix[nextNode_i][nextNode_j];//delta;
	}
}
