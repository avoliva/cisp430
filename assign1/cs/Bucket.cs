/**
 * @author Adam Voliva
 * @description CISP 430 Data Structures
 * @name Assignment 1 Hash Table
 * @date February 5, 2013
 * @file Bucket.cs
 */

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace HashTable
{
    [Serializable]
    class Bucket
    {
        private const int MAX_SLOTS = 3;
        public int count;
        public int overflow;
        public List<Dictionary<string, Slot>> slots;

        // Default constructor
        public Bucket()
        {
            this.count = 0;
            this.overflow = -1;
            this.slots = new List<Dictionary<string, Slot>>();

            // Each Bucket contains 3 slot objects, represented here by a list.
            for (int i = 0; i < MAX_SLOTS; ++i)
            {
                this.slots.Add(new Dictionary<string, Slot>());
            }

        }
    }
}
