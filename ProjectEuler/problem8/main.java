import java.io.IOException;
import java.io.FileInputStream;
import java.io.*;
import java.util.*;

public class main
{
    public static void main(String[] args)
    {
        //File file = new File("file.txt");
        try{
            FileInputStream inputStream = new FileInputStream("file.txt");
            ArrayList<Double> answer = new ArrayList<Double>(13);
            int data = 0; 
            ArrayList<Double> queue = new ArrayList<Double>(13);
            for(int i = 0; i < 13; i++)//Fence posting first 13
            {
                data = inputStream.read(); 
                double newInput = ((double) Character.getNumericValue(data)); 
                queue.add(newInput);
                System.out.println(queue);
            }
            double highScore = 0;
            double currentScore = 1;
            while(data != -1){
                System.out.println("High score: " +highScore);
                int size = queue.size();
                for(int j = 0; j < size; j++)
                {
                    currentScore = currentScore * queue.get(j);
                }
                if(highScore < currentScore){
                    highScore =  currentScore;
                    System.out.println(highScore);
                    answer.clear();
                    for(int k = 0; k < size ; k++)
                    {
                        answer.add(queue.get(k));
                    }
                }
                queue.remove(0);
                double nextInput = ((double)  Character.getNumericValue(inputStream.read())); 
                data = ((int)nextInput);
                queue.add(nextInput);
                currentScore = 1;
            }
            System.out.println(highScore);
            System.out.println("Final answer queue: " + answer);
            System.out.println(queue);
            double finalOutput = 1;
            for(int x = 0; 0 < 13; x++){
                finalOutput *= answer.get(x);
                System.out.println("Final: " + finalOutput);
            }
            //System.out.println("Final: " + finalOutput);
        }catch(Exception ex)
        {
            ex.printStackTrace();
        }
    }
}
