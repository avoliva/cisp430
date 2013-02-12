/**
 * @author Adam Voliva
 * @description CISP 430 Data Structures
 * @name Assignment 1 Hash Table
 * @date February 5, 2013
 * @file Main.cs
 */

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;


namespace HashTable
{
    class Program
    {
        static void Main(string[] args)
        {
            // Hash Table object.
            Table ht = new Table();
            try
            {
                // Read Datain.dat file
                string[] lines = System.IO.File.ReadAllLines(@"C:\Users\Owner\Documents\cisp430\git\assign1\datain.dat");
                foreach (string line in lines)
                {
                    // Insert the data
                    ht.Insert(ht.Hash(line.Substring(0, 10)), line.Substring(10, 20), line.Substring(0, 10));
                }

                // Generate the 'before' report.
                string[] report = ht.GenerateReport();
                System.IO.File.WriteAllLines(@"C:\Users\Owner\Documents\cisp430\git\assign1\before.txt", report);

                // Save the data structure to a file
                ht.SaveDataStructure(@"C:\Users\Owner\Documents\cisp430\git\assign1\saved_table.txt", ht.table);
               
                // Erase the data structure
                ht.table = null;

                // Restore the data structure from the file
                ht.table = (List<Bucket>)ht.RestoreDataStructure(@"C:\Users\Owner\Documents\cisp430\git\assign1\saved_table.txt");

                // Generate the after report
                report = ht.GenerateReport();
                System.IO.File.WriteAllLines(@"C:\Users\Owner\Documents\cisp430\git\assign1\after.txt", report);

                // Generate the 'search and retrieval report' 
                string[] searches = System.IO.File.ReadAllLines(@"C:\Users\Owner\Documents\cisp430\git\assign1\search.dat");
                string[] result = ht.Search(searches);
                System.IO.File.WriteAllLines(@"C:\Users\Owner\Documents\cisp430\git\assign1\retrieval.txt", result);

                // Collect Bucket statistics
                string[] stats = ht.CollectStatistics();
                System.IO.File.WriteAllLines(@"C:\Users\Owner\Documents\cisp430\git\assign1\stats.txt", stats);
            }
            // Many exceptions to handle, mostly IO errors.
            catch (Exception e)
            {
                throw (e);
            }
       
            // Pause at the end
            Console.ReadLine();
            
        }
    }
}
