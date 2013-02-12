/**
 * @author Adam Voliva
 * @description CISP 430 Data Structures
 * @name Assignment 1 Hash Table
 * @date February 5, 2013
 * @file Table.cs
 */



using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Runtime.Serialization;
using System.Runtime.Serialization.Formatters;
using System.Runtime.Serialization.Formatters.Binary;

namespace HashTable
{ 
    [Serializable] 
    class Table
    {
        public List<Bucket> table;
        public const int MAX_SLOTS = 3;
        public const int MAX_BUCKETS = 30;
        public const int OVERFLOW_SIZE = 10;
        public const int PRIMARY_TABLE_SIZE = 20;

        // Default constructor
        public Table()
        {
            this.table = new List<Bucket>();

            // Allocates MaxBucket amount of buckets for each hash table.
            for (int i = 0; i < MAX_BUCKETS; ++i)
            {
                this.table.Add(new Bucket());
            }
        }


        /**
         * Collect bucket statistics
         * 
         * @returns {string[]} Array of strings that can be written to a file
         * @api public
         */
        public string[] CollectStatistics()
        {
            List<string> lines = new List<string>();
            List<int> chain = new List<int>();
            Dictionary<int, int> chain_count = new Dictionary<int, int>();

            float chain_avg = 0F;
            float total_length_avg = 0F;
            float total_length = 0F;
            float non_zero_length_buckets = 0F;

            for (int i = 20; i < MAX_BUCKETS; ++i)
            {
                // if overflow is set
                if (this.table[i].overflow != -1)
                {
                    // if overflow is greater than table size, do some weird math stuff.
                    // this accounts for overflows of overflows.
                    // else add to the list normally.
                    if (this.table[i].overflow + 1 >= PRIMARY_TABLE_SIZE)
                    {
                        chain.Add((this.table[i].overflow + 1) - (PRIMARY_TABLE_SIZE - 1));
                    }
                    else
                    {
                        chain.Add(this.table[i].overflow + 1);
                    }
                }
                else
                {
                    //if no overflow is set, just add 0 (not -1)
                    chain.Add(0);
                }
                // if the chain_count dicitionary contains this key and overflow is also set
                if (!chain_count.ContainsKey(i) && this.table[i].overflow != -1)
                {
                    // ternary statement. this math accounts for overflow of overflows.
                    int index = (this.table[i].overflow + 1 >= PRIMARY_TABLE_SIZE) ? 
                        (this.table[i].overflow + 1) - (PRIMARY_TABLE_SIZE - 1) : this.table[i].overflow + 1;
                    
                    // counts number of instance index appears in the dictionary
                    chain_count[index] = chain.Count(v => v == index);
                    
                    // add to the collission chain average
                    chain_avg += chain_count[index];
                }
            }

            // calculate the collission chain avrage
            chain_avg /= chain_count.Count();

            for (int i = 0; i < PRIMARY_TABLE_SIZE; ++i)
            {
                // grab the total length of each bucket
                total_length += this.table[i].count;

                // write to the list, which then will be returned and can be used to write to a file.
                lines.Add("Bucket " + (i + 1) + ":");
                lines.Add("\tTotal Length: " + this.table[i].count);
                lines.Add("\n");

                // if count is greater than 1, 
                // +1 to the number of buckets which have a more than one slot filled
                // the requirements state not to cound zero length buckets in the average caluclations
                if (this.table[i].count != 0)
                {
                    ++non_zero_length_buckets;
                }
            }

            // calculate the average total length of all primary buckets
            total_length_avg = total_length / non_zero_length_buckets;

            lines.Add("Total Length Average is " + total_length_avg);
            lines.Add("Collission Chain Average is " + chain_avg);

            return lines.ToArray();
        }

        /**
         * Searches and retrieves matches using the values from the param
         * 
         * @param {string[]} Array of items to search for
         * @returns {string[]} Results of the search in an array, which can be used to write to a file
         * @api public
         */
        public string[] Search(string[] searches)
        {
            bool found;
            int bucket_no;
            int slot_no;

            List<String> lines = new List<String>();

            lines.Add(String.Format("{0,45}", "Search and Retrieval Report"));
            lines.Add(String.Format("{0,38}", "Transactions"));
            lines.Add(String.Format("{0,37}", "Search Key\t\tBucket/Slot\t\tRecord"));

            foreach (string keys in searches)
            {
                // hashed key
                string key = this.Hash(keys.Substring(0, 10));

                found = false;
                bucket_no = 0;
                foreach (Bucket item in this.table)
                {
                    slot_no = 0;
                    foreach(Dictionary<string, Slot> dict in item.slots)
                    {
                        foreach (KeyValuePair<string, Slot> kv in item.slots[slot_no])
                        {
                            
                            // if the two un-hashed keys are equal
                            if (item.slots[slot_no][kv.Key].key == keys.Substring(0, 10))
                            {
                                // found
                                found = true;
                                lines.Add(String.Format("{0,16}{1,16}/{2}\t\t{3}", item.slots[slot_no][kv.Key].key,
                                    bucket_no + 1,
                                    slot_no + 1,
                                    item.slots[slot_no][kv.Key].value
                                ));
                            }
                        }
                        // manual iteration
                        ++slot_no;
                    }
                    // manual iteration
                    ++bucket_no;
                }
                // if nothing was found
                if (!found)
                {
                    lines.Add(String.Format("{0,16}{1,16}/{2,0}\t\t{3,0}",
                        keys.Substring(0, 10),
                        "N",
                        "A",
                        "Record not found"
                    ));
                }
            }
            return lines.ToArray();
        }

        /**
         * Restores a data structure that was previously written to a file
         * 
         * @param {string} The file path where this data structure is stored
         * @return {Object} A generic object. This function can be used to restore any data type.
         * @api public
         */
        public Object RestoreDataStructure(string filepath)
        {
            // the data structure can be any data type
            Object DataStructure = null;
            try
            {
                FileStream stream = new FileStream(filepath, 
                    FileMode.Open);

                // BinaryFormatter and Deserialize restores the data from it's raw binary format
                IFormatter formatter = new BinaryFormatter();
                DataStructure = (List<Bucket>)formatter.Deserialize(stream);

                stream.Close();
            }
            catch (Exception e)
            {
                throw (e);
            }
            return DataStructure;
        }

        /**
         * Saves a data structure to a file
         * 
         * @param1 {string} The filepath to which the data will be stored in
         * @param2 {Object} A generic object. This function can store any data type.
         * @api public
         */
        public void SaveDataStructure(string filepath, Object DataStructure)
        {
            Stream stream = null;
            try
            {
                stream = new FileStream(filepath, 
                    FileMode.Create, FileAccess.Write, FileShare.None);
                
                // BinaryFormatter and Serialize output the data in raw binary form
                IFormatter formatter = new BinaryFormatter();
                formatter.Serialize(stream, DataStructure);
                stream.Close();
            }
            catch (Exception e)
            {
                throw(e);
            }
            finally
            {
                if (stream != null)
                    stream.Close();
            }
        }

        /**
         * Generates a report for of the Hash Table contents
         * 
         * @returns {string[]} A string array which can be written to a file.
         * @api public
         */
        public string[] GenerateReport()
        {
            List<String> lines = new List<String>();
            int table_no = 0;
            int slot_no;

            lines.Add(String.Format("{0, 37}", "Hash Table"));
            lines.Add(String.Format("{0, 41}", "Verification Report"));
            lines.Add(String.Format("{0, 39}", "Before Report"));

            foreach (Bucket item in this.table)
            {
                lines.Add(String.Format("Bucket {0}", table_no + 1));
                slot_no = 0;
                foreach (Dictionary<string, Slot> dict in item.slots)
                {
                    foreach (KeyValuePair<string, Slot> kv in item.slots[slot_no])
                    {
                        // if there is a key in the slot
                        if (item.slots[slot_no][kv.Key].key != null)
                        {
                            lines.Add(String.Format("\tSlot {0}: {1}{2}",
                                slot_no + 1,
                                item.slots[slot_no][kv.Key].key,
                                item.slots[slot_no][kv.Key].value
                            ));
                        }
                     
                    }
                    // there must be no key
                    if (item.slots[slot_no].Count == 0)
                    {
                        lines.Add(String.Format("\tSlot {0}: None", slot_no + 1));
                    }
                   // manual iteration
                    ++slot_no;
                }
                // if an overflow pointer is set
                if (this.table[table_no].overflow != -1)
                {
                    lines.Add(String.Format("\tOverflow Pointer: {0}", this.table[table_no].overflow + 1));
                }
                else
                {
                    lines.Add(String.Format("\tOveflow Pointer: {0}", "None"));
                }
                lines.Add(String.Format("{0}", "\n"));
                // manual iteration
                ++table_no;
            }
            return lines.ToArray();
        }

        /**
         * A simple hash function
         * 
         * @param They key to be hashed
         * @returns {string} The hashed key
         * @api public
         */
        public string Hash(string key)
        {
            // Hash algorithm is (Ord(key[2]) + Ord(key[4]) + Ord(key[6])) mod  primary table size\
            // Ord meaning ordinal value
            return (((int)key[2] + (int)key[4] + (int)key[6]) % PRIMARY_TABLE_SIZE).ToString();
        }

        /**
         * Inserts keys and values into the Hash Table
         * 
         * @param1 {string} The hashed key
         * @param2 {string} The value
         * @param3 {string} The un-hashed key
         * @api public
         */
        public void Insert(string hash, string value, string key)
        {
            // A tuple is an object that contains two or more data types within it
            // they don't require any kind of relation at all.
            Tuple<Object, int> tup = this.CollissionCheck(hash);
            int index;
            int length;
            
            // if the first item is not null
            if (tup.Item1 != null)
            {
                //collission is true
                index = tup.Item2;
                if (this.table[index].count > 2)
                {
                    //overflow is true
                    index = this.CheckAvailableBuckets(hash, PRIMARY_TABLE_SIZE, MAX_BUCKETS);
                    length = this.table[index].count;
                    if (length > 2)
                    {
                        //overflow of overflow is true
                        index = this.CheckAvailableBuckets(hash, index + 1, MAX_BUCKETS);
                        length = this.table[index].count;
                    }
                    if (length > 0)
                    {
                        //insert into old overflow bucket
                        this.table[index].slots[length][hash] = new Slot();
                        this.table[index].slots[length][hash].key = key;
                        this.table[index].slots[length][hash].value = value;
                        this.table[index].count += 1;
                    }
                    else
                    {
                        // new overflow bucket
                        this.table[index].slots[0][hash] = new Slot();
                        this.table[index].slots[0][hash].key = key;
                        this.table[index].slots[0][hash].value = value;
                        this.table[index].count += 1;
                        this.SetOverflowPointer(index, hash);
                    }
                }
                else
                {
                    // overflow is false, collission still true
                    length = this.table[index].count;
                    this.table[index].slots[length][hash] = new Slot();
                    this.table[index].slots[length][hash].key = key;
                    this.table[index].slots[length][hash].value = value;
                    this.table[index].count += 1;
                }
            }
            else
            {
                // brand new key
                index = this.CheckAvailableBuckets(hash, 0, PRIMARY_TABLE_SIZE);
                length = this.table[index].count;
                this.table[index].slots[length][hash] = new Slot();
                this.table[index].slots[length][hash].key = key;
                this.table[index].slots[length][hash].value = value;
                this.table[index].count += 1;
            }
        }

        /**
         * Sets the overflow pointer to its proper value
         * 
         * @param1 {int} The list index of the overflow pointer to be set
         * @param2 {string} The hashed key used to check any available buckets
         * @api private
         */
        private void SetOverflowPointer(int index, string key)
        {
            int of_index = this.CheckAvailableBuckets(key, 0, PRIMARY_TABLE_SIZE);

            // don't want to erase any old overflow pointer values. this will help for overflow of overflows.
            this.table[index].overflow = (this.table[index].overflow == -1) ? of_index : this.table[index].overflow;
            this.table[of_index].overflow = (this.table[of_index].overflow == -1) ? index : this.table[of_index].overflow;

            // this is for the pointer of overflow of overflows 
            of_index = this.CheckAvailableBuckets(key, PRIMARY_TABLE_SIZE, MAX_BUCKETS);
            if (of_index != index)
                this.table[index].overflow = of_index;
        }

        /**
         * Checks for any collissions in the Hash Table
         * 
         * @param {string} The hashed key
         * @returns {Tuple<Object, int>} A tuple containing a generic object and index of the collission
         * @api private
         */
        private Tuple<Object, int> CollissionCheck(string key)
        {
            int bucket_no = 0;
            foreach(Bucket item in this.table)
            {
                foreach(Dictionary<string, Slot> dict in item.slots)
                {
                    if (dict.ContainsKey(key))
                    {
                        return new Tuple<Object, int>(dict, bucket_no);
                    }
                }
                // manual iteration
                ++bucket_no;
            }
            return new Tuple<Object, int>(null, 0);
        }
        
        /**
         * Checks for any available buckets to insert into
         * 
         * @param1 {string} The hashed key
         * @param2 {int} Where to start checking
         * @param3 {int} Where to end checking
         * @returns {int} The index of the next available bucket
         */
        public int CheckAvailableBuckets(string key, int min, int max)
        {
            for (int bucket_no = min; bucket_no < max; ++bucket_no)
            {
                for (int slot_no = 0; slot_no < MAX_SLOTS; ++slot_no) 
                {
                    // if the slot contains a key, return that index
                    if (this.table[bucket_no].slots[slot_no].ContainsKey(key))
                    {
                        return bucket_no;
                    }
                    // if the bucket is empty return that index
                    if (this.table[bucket_no].slots[0].Count == 0)
                    {
                        return bucket_no;
                    }
                }
            }
            // this line should never be reached unless you're inserting too many values
            // and no more overflow buckets remain.
            throw new Exception("Ran out of overflow buckets!");
        }
    }
}