import java.io.*;               //io is a package in java which consists of File Manipulation classes
import java.util.ArrayList;    //CPP cha vector, aree baba resizable array , provides built in function to add , delete , search data in array
import java.util.Collections; //Enables user to perform data manipulation operations like sort(), search(), min(), max(), swap()

public class externalSorting {
    public static void main(String[] args) {
        String inputFileName = "numbers.txt";           //Input File - Structure : Each Number on separate and no blank lines in-between
        String outputFileName = "sorted_numbers.txt";       //Output file

        //Step 1 :- Extracting Numerals from Input file to an ArrayList using user defined function
        ArrayList<Integer> numbers = readNumbersFromFile(inputFileName);

        //Step 2:- Traversing ArrayList & Sorting it
        if (numbers != null) {              // If ArrayList is not empty
            Collections.sort(numbers);      //Follows, Merge Sort - O(n.logn)

            //At this step we have sorted data
            //Step 3:- Copying sorted numbers to file using user defined function
            if (writeNumbersToFile(outputFileName, numbers)) {
                System.out.println("Sorted numbers written to " + outputFileName);
            } else {
                System.out.println("Failed to write sorted numbers to file.");
            }
        } else {
            System.out.println("Failed to read numbers from file.");
        }
    }

    //Defining function to copy numbers from file to ArrayList
    private static ArrayList<Integer> readNumbersFromFile(String fileName) {
        ArrayList<Integer> numbers = new ArrayList<>();            //Declaring ArrayList to store numbers
        try (BufferedReader br = new BufferedReader(new FileReader(fileName))) {    //Reading data line by line using BufferedReader , FileReader is used to read a file
            String line;
            while ((line = br.readLine()) != null) {                //if line that is read is not a blank line
                try {
                    int number = Integer.parseInt(line);                            //type-casting --> String to Integer
                    numbers.add(number);                                            //appends the converted number to ArrayList
                } catch (NumberFormatException e) {
                    System.err.println("Invalid number found: " + line);
                }
            }
        } catch (IOException e) {
            System.err.println("Error reading file: " + e.getMessage());
            return null;
        }
        return numbers;
    }

    //User Defined Function 2 : For writing data from ArrayList to File
    private static boolean writeNumbersToFile(String fileName, ArrayList<Integer> numbers) {
        try (BufferedWriter bw = new BufferedWriter(new FileWriter(fileName))) {    //FileWriter give writing access to file
            for (int number : numbers) {                                    // for number in numbers
                bw.write(Integer.toString(number));                         //TypeCasting --> Integer to String
                bw.newLine();                                               //As we are expected to write a single number on a single line , we write a newline after each number
            }
        } catch (IOException e) {
            System.err.println("Error writing to file: " + e.getMessage());
            return false;
        }
        return true;
    }

    @Override
    public String toString() {
        return "externalSorting []";
    }

}
