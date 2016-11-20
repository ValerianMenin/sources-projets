/**
 * 
 */
package polytech.tours.di.parallel.tsp;

import java.util.concurrent.Callable;
//import java.util.ArrayList;
import java.util.Collections;
//import java.util.List;
import java.util.concurrent.ThreadLocalRandom;

/**
 * LocalSearcher is used to create a random solution and find the best implovement of it
 * @author Valerian Menin
 */
class LocalSearcher implements Callable<Solution>
{
	/**
	 * attributs
	 */
	private Solution bestLocalSolution;
	private Instance instance;
	private TSPCostCalculator TSPCostCalculator;
	
	/**
	 * initialize bestLocalSolution with a random solution : S_0
	 * it is only called when a LocalSearcher is created
	 */
	private void createRandomInitialSolution()
	{// TODO amélioration : initialize the randomSolution with some cities all close. Longer to create but faster to optimize
		//int randomPercent = 1;
		//ArrayList unusedElement // 
		//int bestFollowingNode[] = new int[(int)randomPercent*instance.getN()/100+3];//we assume we have more than 4 elements on our instance
		//System.out.println(bestFollowingNode.length);
		for (int i = 0; i < instance.getN(); i++)
		{
			bestLocalSolution.add(i);
			Collections.shuffle(bestLocalSolution, ThreadLocalRandom.current());
		}
		bestLocalSolution.setOF(TSPCostCalculator.calcOF(instance.getDistanceMatrix(), bestLocalSolution));//on calcule la distance
	}
	
	/**
	 * LocalSearcher's constructor
	 * @param instance the instance to read
	 */
	public LocalSearcher(Instance instance)
	{
		this.instance = instance;
		bestLocalSolution = new Solution(); // create an empty solution
		TSPCostCalculator = new TSPCostCalculator(); // create a copy of the calculator
	}
	
	/**
	 * use the random solution S_0 to make it better
	 * a maximum of <code>maxLoop<\code> changed is accepted. If we reach it, we assume that the solution is good enough
	 * 		the higher mexLoop is, the closer to the best local solution we could find but the slower it is because of the number of steps
	 * @return <code>true<\code> when we found the best local solution or reached maxLoop steps (finish processing)
	 */
	private void optimiseSolution() 
	{
		//System.out.println("init\t"+bestLocalSolution);
		//instance.printDistanceMatrix("#");
		
		boolean bestLocalSolutionReached = false;
		long maxLoop = 10000;//used to make it faster the lower it is, the faster it is. But the lower it is the less precise it is
		while(bestLocalSolutionReached==false && maxLoop>0)
		{
			if(twoOptBestImprovement())
				if(relocateBestImprovement())
					if(swapBestImprovement())
						bestLocalSolutionReached = true;
			maxLoop--;
		}
	}
	
	/**
	 * make relocate until we explored all relocate possible or until we find a better solution
	 * @return true if their is no any change : it has been optimized with relocating method
	 * or
	 * @return false if we found a better solution
	 */
	private boolean relocateBestImprovement() 
	{
		for(int i=0; i<instance.getN(); i++)
			for (int j=0; j<instance.getN(); j++)
			{
				double deltaOF=TSPCostCalculator.relocateOf(i,j, bestLocalSolution);
				if(deltaOF<0)//si il y a un gain, on fait le swap
				{
					//System.out.println("avant "+bestLocalSolution);
					bestLocalSolution.relocate(i, j);//swap
					bestLocalSolution.setOF(deltaOF+bestLocalSolution.getOF());//new OF
					//System.out.println("apres "+bestLocalSolution);
					return false;
				}
			}
		//System.out.println("bestRelocate "+bestLocalSolution);
		return true;
	}
	
	/**
	 * make swap until we explored all relocate possible or until we find a better solution
	 * @return true if their is no any change : it has been optimized with swapping method
	 * or
	 * @return false if we found a better solution
	 */
	private boolean swapBestImprovement() 
	{
		for(int i=0; i<instance.getN()-1; i++)
			for (int j=i+1; j<instance.getN(); j++)
			{	
				double deltaOF=TSPCostCalculator.swapOf(i,j, bestLocalSolution);
				//System.out.println("i="+i + " | j="+j+" | deltaOF="+deltaOF );
				if(deltaOF<0)//si il y a un gain, on fait le swap
				{
					//System.out.println("avant "+bestLocalSolution);
					bestLocalSolution.swap(i, j);//swap
					bestLocalSolution.setOF(deltaOF+bestLocalSolution.getOF());//new OF
					//System.out.println("apres "+bestLocalSolution);
					return false;
				}
			}
		//System.out.println("bestSwap "+bestLocalSolution);
		return true;
	}
	
	/**
	 * make <code>2opt<\code> until we explored all relocate possible or until we find a better solution
	 * @return true if their is no any change : it has been optimized with <code>2opt<\code> method
	 * or
	 * @return false if we found a better solution
	 */
	private boolean twoOptBestImprovement() 
	{
		int nbOfNodes = instance.getN();
		for(int i=0; i<nbOfNodes; i++)
			for (int j=(i+2+nbOfNodes)%nbOfNodes; j!=(i-1+nbOfNodes)%nbOfNodes; j=(++j+nbOfNodes)%nbOfNodes)
			{
				double deltaOF=TSPCostCalculator.twoOptOf(i, j, bestLocalSolution);
				//System.out.println("[i, j]=["+i +", "+j+ " | deltaOF="+deltaOF );
				if(deltaOF<0)//si il y a un gain, on fait le swap
				{
					//System.out.println("avant "+bestLocalSolution);
					twoOpt(i, j);
					bestLocalSolution.setOF(deltaOF+bestLocalSolution.getOF());//new OF
					//System.out.println("apres "+bestLocalSolution);
					return false;
				}
			}
		return true;
	}
	
	/**
	 * 2opt the element in position <code>i</code> and the element in position <code>j</code>. The method
	 * only manipulates the permutation; it does not up update the objective function or any other attribute of the encode solution.
	 * Client classes are responsible to update the attributes of the solution.
	 * @param i the first 2opt position. 0 <= i< {@link #size()}
	 * @param j the second 2opt position. 0 <= j< {@link #size()}
	 */
	public void twoOpt(int i, int j){
		int lastNodeToSwap = (i+j)/2;
		//int indice=0;
		//System.out.println("[i, j, lastSwap]=["+i+", "+j+", "+lastNodeToSwap+"]");
		while(i<lastNodeToSwap){
			//System.out.println(i+" "+this);
			bestLocalSolution.swap(++i, j--);
		}
	}
	
	@Override
	public Solution call() throws Exception 
	{
		createRandomInitialSolution(); // création de la solution initiale
		optimiseSolution(); // fonction qui va effectuer des swat, relocate et 2opt jusqu'à ne plus avoir de changements
		//System.out.println(bestLocalSolution);
		return bestLocalSolution;
	}
}
