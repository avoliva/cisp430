/**
 * @author Adam Voliva
 * @description CISP 430 Data Structures
 * @name Assignment 1 Hash Table
 * @date February 5, 2013
 * @file Slot.cs
 */

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace HashTable
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
}
