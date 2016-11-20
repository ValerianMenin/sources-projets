/**
 * 
 */
package polytech.tours.di.parallel.tsp;

import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Properties;
import java.util.concurrent.Callable;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;

/**
 * implements the algorithm of the Travelling Salesman Problem
 * @author Valerian Menin
 */
class MyTSP implements Algorithm {

	
	@Override
	public Solution run(Properties config) 
	{
		Solution bestSolution = new Solution();
		
		int numberOfThreads = Integer.parseInt(config.getProperty("threads")); // max 8 (8 core)
		int numberOfTask = Integer.parseInt(config.getProperty("iterations"));//100 // number of "random solution" generated
		
		ExecutorService executor = Executors.newFixedThreadPool(numberOfThreads);
		
		List<Future<Solution>> localOptima = null; // list of LocalSearch Solution
		List<Callable<Solution>> tasks = new ArrayList<>(); // list of task
		
		// read file create instance
		InstanceReader graph = new InstanceReader(); // an Instance is a graph
		graph.buildInstance(config.getProperty("instance"));
		Instance instance = graph.getInstance();
		
		long beginningTime, endingTime;
		beginningTime = System.nanoTime();
		
		// create all task
		for(int t = 0; t < numberOfTask; t++)
		{
			tasks.add(new LocalSearcher(instance));
		}
		
		// execute all task
		try
		{
			localOptima = executor.invokeAll(tasks);
		} 
		catch (InterruptedException e1) 
		{
			e1.printStackTrace();
		}
		
		// compare to find the best Solution in localOptima
		try {
			bestSolution = localOptima.get(0).get();
		} catch (InterruptedException | ExecutionException e1) {
			e1.printStackTrace();
		}
		for(int t = 1; t < numberOfTask; t++)
		{
			try 
			{
				if(localOptima.get(t).get().getOF() < bestSolution.getOF())
				bestSolution = localOptima.get(t).get(); // to have Solution
			} catch (InterruptedException | ExecutionException e1) {
				e1.printStackTrace();
			}
		}

		endingTime = System.nanoTime();
		long deltaTime = endingTime - beginningTime;
		long ns = deltaTime%1000;
		long ms = (deltaTime%1000000)/1000;
		long sec = (deltaTime/1000000000)%60;
		long min = ((deltaTime/1000000000)-sec)/60;
		String fileName = config.getProperty("instance").substring(7);
		
		System.out.println(fileName+"\t"
				+numberOfThreads+"\t"
				+numberOfTask+"\t"
				+ bestSolution.getOF()+"\t"
				+deltaTime);
		
		/*System.out.println("With "+numberOfThreads+" threads and "
				+numberOfTask+" tasks. For "
				+ fileName +", we found "
				+ bestSolution.getOF() +" with an execution time of "
				+deltaTime+"mn\t: "+min+" min, "+sec+" sec, "+ms+" ms, "+ns+" ns");*/
		writeResultOnFile(fileName, numberOfThreads, numberOfTask, bestSolution.getOF(), deltaTime, min, sec, ms, ns);
		return bestSolution;
	}
	
	/**
	 * Write the most important informations on the file results.csv it is used to compare our methods, numberOfThreads, numberOfTask ...
	 * @param fileName the instance's name
	 * @param numberOfThreads the number of threads
	 * @param numberOfTask the umber of iterations
	 * @param of the distance reached by the best solution
	 * @param deltaTime the time to reached the best solution in nanoseconde
	 * @param min
	 * @param sec
	 * @param ms
	 * @param ns
	 */
	private void writeResultOnFile(String fileName, int numberOfThreads, int numberOfTask, double of, long deltaTime, long min, long sec, long ms, long ns)
	{		
		String data = fileName+";"+numberOfThreads+";"+numberOfTask+";"+of+";"+deltaTime+";"+min+";"+sec+";"+ms+";"+ns+";\n";
		
		//File f = new File ("results.txt");
		 
		try
		{
		    FileWriter fw = new FileWriter ("results.csv", true);
		        fw.write (data);
		    fw.close();
		}
		catch (IOException exception)
		{
		    System.out.println ("Error writeResultOnFile : " + exception.getMessage());
		}
	}
}


