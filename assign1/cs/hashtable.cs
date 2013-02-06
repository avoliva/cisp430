/*
@author Adam Voliva
@description CISP 430 Data Structures
@name Assignment 1 Hash Table
@date February 6, 2013
@file hashtable.cs
*/


using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Runtime.Serialization;
using System.Runtime.Serialization.Formatters;
using System.Runtime.Serialization.Formatters.Binary;

/*
const int MaxSlots = 3;
const int MaxBuckets = 30;
const int TableSize = 20;
const int OverflowSize = 10;
 * */

namespace hashtable
{
    [Serializable]
    class Slot
    {
        public string key;
        public string value;
        public Slot()
        {
            this.key = null;
            this.value = null;
        }
    }

    [Serializable] 
    class Bucket
    {
        public int count;
        public int overflow;
        public List<Dictionary<string, Slot>> slots;
        //public Dictionary<Slot, string> somedict;
        public Bucket()
        {
            this.count = 0;
            this.overflow = -1;
            this.slots = new List<Dictionary<string, Slot>>();
            for (int i = 0; i < 3; ++i)
            {
                this.slots.Add(new Dictionary<string, Slot>());
            }

        }
    }

    [Serializable] 
    class HashTable
    {
        public List<Bucket> table;
        public HashTable()
        {
            this.table = new List<Bucket>();
            for (int i = 0; i < 30; ++i)
            {
                this.table.Add(new Bucket());
            }
            //List<Bucket> table = new List<Bucket>();
        }

        public void SaveReport()
        {
            Stream stream = null;
            try
            {
                IFormatter formatter = new BinaryFormatter();
                stream = new FileStream(@"C:\Users\Owner\Documents\cisp430\git\assign1\hashtable.txt", FileMode.Create, FileAccess.Write, FileShare.None);
                formatter.Serialize(stream, this.table);
            }
            catch
            {
                // do nothing
            }
            finally
            {
                if (null != stream)
                    stream.Close();
            }
        }
        public void GenerateReport()
        {
            List<String> lines = new List<String>();
            //lines.Add("Hash Table"
            lines.Add(String.Format("{0, 45}", "Hash Table"));
            lines.Add(String.Format("{0, 49}", "Verification Report"));
            lines.Add(String.Format("{0, 46}", "Before Report"));
            int i = 0;
            foreach (Bucket item in this.table)
            {
                lines.Add(String.Format("Bucket {0}", i + 1));
                int j = 0;
                foreach (Dictionary<string, Slot> dict in item.slots)
                {
                    int k = 0;
                    foreach (KeyValuePair<string, Slot> kv in item.slots[j])
                    {
                        
                        if (item.slots[j][kv.Key].key != null)
                        {
                            lines.Add(String.Format("\tSlot {0}: {1}{2}",
                                j + 1,
                                item.slots[j][kv.Key].key,
                                item.slots[j][kv.Key].value
                            ));
                        }
                        ++k;
                        //Console.WriteLine(k);
                     
                    }
                    if (item.slots[j].Count == 0)
                    {
                        lines.Add(String.Format("\tSlot {0}: None", j + 1));
                    }
                   // Console.WriteLine(j);
                    ++j;
                }
                if (this.table[i].overflow != -1)
                {
                    lines.Add(String.Format("\tOverflow Pointer: {0}", this.table[i].overflow + 1));
                }
                else
                {
                    lines.Add(String.Format("\tOveflow Pointer: {0}", "None"));
                }
                lines.Add(String.Format("{0}", "\n"));
                ++i;
            }
            string[] text = lines.ToArray();
            System.IO.File.WriteAllLines(@"C:\Users\Owner\Documents\cisp430\git\assign1\before.txt", text);
        }
          
        public void DataIn()
        {
            //Object file = System.IO.File.Open('datain.dat', 'r+');
            //FileStream file = new FileStream(@"c:\datain.dat", FileMode.Open, FileAccess.Read);
            string[] lines = System.IO.File.ReadAllLines(@"C:\Users\Owner\Documents\cisp430\git\assign1\datain.dat");
            foreach (string line in lines)
            {
                this.Insert(this.Hash(line.Substring(0, 10)), line.Substring(10, 20), line.Substring(0, 10));
            }
        }

        public string Hash(string key)
        {
            return (((int)key[2] + (int)key[4] + (int)key[6]) % 20).ToString();
        }

        public void Insert(string key, string value, string data)
        {
            Tuple<Object, int> tup = this.CollissionCheck(key);
            if (tup.Item1 != null)
            {
                //collission is true
                //Dictionary<string, string> item = (Dictionary<string, string>)tup.Item1;
                int index = tup.Item2;
                if (this.table[index].count > 2)
                {
                    //overflow is true
                    //Console.WriteLine("overflow is true");
                    index = this.CheckAvailableBuckets(key, 20, 30);
                    int length = this.table[index].count;
                    Console.WriteLine("length is " + length);
                    if (length == 3)
                    {
                        //overflow of overflow is true
                        //Console.WriteLine("overflow of overflow is true");
                        index = this.CheckAvailableBuckets(key, index + 1, 30);
                        length = this.table[index].count;
                    }
                    if (length > 0)
                    {
                        //insert into old overflow bucket
                        //Console.WriteLine("insert into old overflow bucket");
                        this.table[index].slots[length][key] = new Slot();
                        this.table[index].slots[length][key].key = key;
                        this.table[index].slots[length][key].value = value;
                        this.table[index].count += 1;
                    }
                    else
                    {
                        // new overflow bucket
                        //Console.WriteLine("new overflow bucket");
                        this.table[index].slots[0][key] = new Slot();
                        this.table[index].slots[0][key].key = key;
                        this.table[index].slots[0][key].value = value;
                        this.table[index].count += 1;
                        this.SetOverflowPointer(index, key);
                    }
                }
                else
                {
                    // overflow is false, collission still true
                    //Console.WriteLine("overflow is false, collission still true");
                    int length = this.table[index].count;
                    //Console.WriteLine(length);
                    //Console.WriteLine(key);
                    this.table[index].slots[length][key] = new Slot();
                    this.table[index].slots[length][key].key = key;
                    this.table[index].slots[length][key].value = value;
                    this.table[index].count += 1;
                    //Console.WriteLine("index is " + index);
                }
            }
            else
            {
                // brand new key
                //Console.WriteLine("brand new key");
                int index = this.CheckAvailableBuckets(key, 0, 20);
                int length = this.table[index].count;
                this.table[index].slots[length][key] = new Slot();
                this.table[index].slots[length][key].key = key;
                this.table[index].slots[length][key].value = value;
                this.table[index].count += 1;
                //Console.WriteLine("index is " + index);
            }
        }

        public void SetOverflowPointer(int index, string key)
        {
            int of_index = this.CheckAvailableBuckets(key, 0, 20);
            this.table[index].overflow = (this.table[index].overflow == -1) ? of_index : this.table[index].overflow;
            this.table[of_index].overflow = (this.table[of_index].overflow == -1) ? index : this.table[of_index].overflow;
            // this is for the pointer of overflow of overflows 
            of_index = this.CheckAvailableBuckets(key, 20, 30);
            if (of_index != index)
                this.table[index].overflow = of_index;
            Console.WriteLine(of_index);
            Console.WriteLine("index = " + index);
        }

        public Tuple<Object, int> CollissionCheck(string key)
        {
            int i = 0;
            foreach(Bucket item in this.table)
            {
                foreach(Dictionary<string, Slot> dict in item.slots)
                {
                    //foreach(string k in dict.Keys)
                    //{
                        if (dict.ContainsKey(key))
                        {
                            return new Tuple<Object, int>(dict, i);
                        }
                    //}
                }
                ++i;
            }
            return new Tuple<Object, int>(null, 0);
        }
        
        public int CheckAvailableBuckets(string key, int min, int max)
        {
            for (int i = min; i < max; ++i)
            {
                for (int j = 0; j < 3; ++j) 
                {
                    //foreach(Slot k in this.table[i].slots[j].Keys)
                    //{
                        if (this.table[i].slots[j].ContainsKey(key))
                        {
                            //Console.WriteLine("now i is " + i + " and j is " + j);
                            return i;
                        }
                        if (this.table[i].slots[0].Count == 0)
                        {
                            //Console.WriteLine("i is " + i + ", j is " + j);
                            return i;
                        }

                    //}
                }
            }
            return 0;
        }
    }

    class TestClass
    {
        static void Main(string[] args)
        {
            // Display the number of command line arguments:
            //Bucket shit = new Bucket();
            /*foreach(Slot key in shit.somedict.Keys)
            {
                Console.WriteLine(key.key);
            }*/

            HashTable ht = new HashTable();
            /*
            ht.Insert("key", "data", "keydata");
            ht.Insert("key", "data", "keydata");
            ht.Insert("key", "data", "keydata");
            ht.Insert("key", "data", "keydata");
            ht.Insert("key", "data", "keydata");
            ht.Insert("key", "data", "keydata");
            ht.Insert("key", "data", "keydata");
             * */

            ht.DataIn();
            ht.GenerateReport();
            ht.SaveReport();

            Console.ReadLine();
        }
    }
}