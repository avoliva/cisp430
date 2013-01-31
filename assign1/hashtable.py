#@author Adam Voliva
#@description CISP 430 Data Structures
#@name Assignment 1 Hash Table
#@date January 31, 2013


import pickle

MaxSlots = 3
MaxBuckets = 30
TableSize = 20
OverflowSize = 10


class Bucket:

    def __init__(self):
        self.count = 0
        self.overflow = None
        self.slots = {}


class HashTable:

    def __init__(self):
        self.table = []
        for i in range(0, MaxBuckets):
            self.table.append(Bucket())

    def Search(self):
        f = open('./search.dat', 'r+')
        for keys in f.readlines():
            for pos, item in enumerate(self.table):
                # how the hell do you know which slot it's in?
                # fucking dixon.
                pass

    def RestoreReport(self):
        if self.table is not None:
            raise Exception('The hash table has been restored already.')
        f = open('./hashtable.txt', 'r+')
        self.table = pickle.load(f)
        f.close()

    def SaveReport(self):
        f = open('./hashtable.txt', 'w+')
        # Pickle dumps a data structure to a file
        pickle.dump(self.table, f)
        f.close()
        # Deleted from memory
        self.table = None

    def GenerateReport(self):
        f = open('./before.txt', 'w+')
        f.write('Hash Table'.center(82))
        f.write('\n')
        f.write('Verififcation Report'.center(82))
        f.write('\n')
        f.write('Before Restoration'.center(82))
        f.write('\n')
        for pos, item in enumerate(self.table):
            f.write('Bucket {0}\n'.format(pos + 1))
            for key, value in item.slots.iteritems():
                for index in range(0, 3):
                    if index in item.slots[key].keys():
                        f.write('\tSlot {0}: {1}\n'.format(index + 1,
                            item.slots[key][index]))
                    else:
                        f.write('\tSlot {0}: \n'.format(index + 1))
            if len(self.table[pos].slots) == 0:
                for index in range(0, 3):
                    f.write('\tSlot {0}: \n'.format(index + 1))
            f.write('Overflow Pointer: {0}\n'.format(
                self.table[pos].overflow))
            f.write('\n')

    def DataIn(self):
        f = open('./datain.dat', 'r+')
        for i in f.readlines():
            self.Insert(self.Hash(i[:10]) % TableSize, i[10:30])
        f.close()

    def Hash(self, key):
        return ord(key[2]) + ord(key[4]) + ord(key[6]) % TableSize

    def Insert(self, key, value):
        tup = self.CollissionCheck(key)
        if tup is not None:
            # collission is true
            item, index = tup
            if 2 in item.keys():
                index = self.CheckAvailableBuckets(key, 19, MaxBuckets)
                # overflow is true
                # length = self.GetTableLength(key, index)
                length = self.table[index].count
                while length == 3:
                    # overflow of overflow is true
                    index = self.CheckAvailableBuckets(key, index + 1,
                        MaxBuckets)
                    length = self.table[index].count
                    # length = self.GetTableLength(key, index)
                if length > 0:
                    # insert into 'old' overflow bucket
                    self.table[index].slots[key][length] = value
                    self.table[index].count += 1
                    self.SetOverflowPointer(index, key)
                else:
                    # new overflow bucket
                    self.table[index].slots[key] = {}
                    self.table[index].slots[key][0] = value
                    self.table[index].count += 1
                    self.SetOverflowPointer(index, key)
            else:
                # overflow is false, collission still true
                length = self.table[index].count
                self.table[index].slots[key][length] = value
                self.table[index].count += 1
                # print item.child()
                # print item.count
        else:
            #brand new key
            index = self.CheckAvailableBuckets(key, 0, TableSize)
            self.table[index].slots[key] = {}
            self.table[index].slots[key][0] = value
            self.table[index].count += 1

    def SetOverflowPointer(self, index, key):
        overflow_index = self.CheckAvailableBuckets(key,
            0, TableSize)
        self.table[index].overflow = overflow_index
        self.table[overflow_index].overflow = index

    def CollissionCheck(self, key):
        for pos, item in enumerate(self.table):
            if key in item.slots:
                return item.slots[key], pos
        return None

    def CheckAvailableBuckets(self, key, minimum, maximum):
        for i in range(minimum, maximum):
            if key in self.table[i].slots.keys():
                return i
            if len(self.table[i].slots.keys()) is 0:
                return i
        # Should never get here
        raise Exception('Ran out of overflow buckets!')


ht = HashTable()

ht.DataIn()

ht.GenerateReport()

ht.SaveReport()

if ht.table is not None:
    raise Exception('The hash table must be deleted from memory.')

ht.RestoreReport()

# print('{0:20} {1}'.format(' ','hash table'.center))
