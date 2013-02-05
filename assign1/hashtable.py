#@author Adam Voliva
#@description CISP 430 Data Structures
#@name Assignment 1 Hash Table
#@date February 5, 2013


# Pickle is a standard Python library
import pickle


# Constants
MaxSlots = 3
MaxBuckets = 30
TableSize = 20
OverflowSize = 10


class Slot(dict):

    def __init__(self):
        self.key = None
        self.value = None


class Bucket:

    def __init__(self):
        self.count = 0
        self.overflow = None
        self.slots = []
        # Slots is a list that contains a dictionary
        # Easier to manage this way.
        for i in range(0, 3):
            self.slots.append({})


class HashTable:

    def __init__(self):
        self.table = []
        # Puts MaxBucket amount of Bucket objects into the list
        for i in range(0, MaxBuckets):
            self.table.append(Bucket())

    def Search(self):
        f = open('./search.dat', 'r+')
        f2 = open('./retrieval.txt', 'w+')
        f2.write('Search and Retrieval'.center(82))
        f2.write('\n')
        f2.write('Transactions'.center(82))
        f2.write('\n')
        f2.write('Search Key\t\tBucket/Slot\t\tRecord'.center(82))
        f2.write('\n')
        for keys in f.readlines():
            key = self.Hash(keys[:10])
            for pos, item in enumerate(self.table):
                for ps, ite in enumerate(item.slots):
                    if key in item.slots[ps]:
                        if keys[:10] == item.slots[ps][key].key:
                            f2.write('{0:>35}{1:>16}/{2}\t\t{3}'.format(
                                item.slots[ps][key].key,
                                pos + 1,
                                ps + 1,
                                item.slots[ps][key].value
                            ))
                            f2.write('\n')
        f.close()
        f2.close()

    def RestoreReport(self):
        # Why restore a structure that still exists?
        if self.table is not None:
            raise Exception('The hash table has been restored already.')
        f = open('./hashtable.txt', 'r+')
        # Loads the file back into memory
        self.table = pickle.load(f)
        f.close()

    def SaveReport(self):
        f = open('./hashtable.txt', 'w+')
        # Pickle dumps a data structure to a file
        pickle.dump(self.table, f)
        f.close()
        # Deleted from memory
        self.table = None

    def GenerateReport(self, fname):
        f = open('./{0}'.format(fname), 'w+')
        f.write('Hash Table'.center(82))
        f.write('\n')
        f.write('Verififcation Report'.center(82))
        f.write('\n')
        f.write('Before Restoration'.center(82))
        f.write('\n')
        for pos, item in enumerate(self.table):
            f.write('Bucket {0}\n'.format(pos + 1))
            for ps, ite in enumerate(item.slots):
                for key, value in item.slots[ps].iteritems():
                    if item.slots[ps][key] is not None:
                        f.write('\tSlot {0}: {1}{2}\n'.format(ps + 1,
                                item.slots[ps][key].key,
                                item.slots[ps][key].value))
                if len(item.slots[ps].keys()) is 0:
                    f.write('\tSlot {0}: None\n'.format(ps + 1))
            if self.table[pos].overflow is not None:
                f.write('Overflow Pointer: {0}\n'.format(
                    int(self.table[pos].overflow) + 1))
            else:
                f.write('Overflow Pointer: {0}\n'.format(
                        self.table[pos].overflow))
            f.write('\n')

    def DataIn(self):
        f = open('./datain.dat', 'r+')
        for line in f.readlines():
            # This syntax grabs part of the string,
            # so it will not grab new line characters
            self.Insert(self.Hash(line[:10]), line[10:30], line[:10])
        f.close()

    def Hash(self, key):
        return (ord(key[2]) + ord(key[4]) + ord(key[6])) % TableSize

    def Insert(self, key, value, data):
        tup = self.CollissionCheck(key)
        if tup is not None:
            # collission is true
            item, ht_index, slot_index = tup
            if self.table[ht_index].count > 2:
                ht_index, slot_index = self.CheckAvailableBuckets(key, 19, MaxBuckets)
                # overflow is true
                length = self.table[ht_index].count
                while length == 3:
                    # overflow of overflow is true
                    ht_index, slot_index = self.CheckAvailableBuckets(key,
                        ht_index + 1, MaxBuckets)
                    length = self.table[ht_index].count
                if length > 0:
                    # insert into 'old' overflow bucket
                    self.table[ht_index].slots[length][key] = Slot()
                    self.table[ht_index].slots[length][key].key = data
                    self.table[ht_index].slots[length][key].value = value
                    self.table[ht_index].count += 1
                    self.SetOverflowPointer(ht_index, key)
                else:
                    # new overflow bucket
                    self.table[ht_index].slots[0][key] = Slot()
                    self.table[ht_index].slots[0][key].key = data
                    self.table[ht_index].slots[0][key].value = value
                    self.table[ht_index].count += 1
                    self.SetOverflowPointer(ht_index, key)
            else:
                # overflow is false, collission still true
                length = self.table[ht_index].count
                self.table[ht_index].slots[length][key] = Slot()
                self.table[ht_index].slots[length][key].key = data
                self.table[ht_index].slots[length][key].value = value
                self.table[ht_index].count += 1
        else:
            #brand new key
            ht_index, slot_index = self.CheckAvailableBuckets(key, 0, TableSize)
            self.table[ht_index].slots[slot_index][key] = Slot()
            self.table[ht_index].slots[slot_index][key].key = data
            self.table[ht_index].slots[slot_index][key].value = value
            self.table[ht_index].count += 1

    def SetOverflowPointer(self, index, key):
        # Sets overflow 'pointer'
        #@todo: have it work for overflow of overflows
        ht_index, temp = self.CheckAvailableBuckets(key,
            0, TableSize)
        self.table[index].overflow = ht_index
        self.table[ht_index].overflow = index

    def CollissionCheck(self, key):
        for pos, item in enumerate(self.table):
            for ps, ite in enumerate(item.slots):
                if key in item.slots[ps]:
                    # Returns a tuple
                    return ite, pos, ps
        # Returns none if there is no collission
        return None

    def CheckAvailableBuckets(self, key, minimum, maximum):
        # Returns a tuple
        for i in range(minimum, maximum):
            for j in range(0, 3):
                if key in self.table[i].slots[j].keys():
                    return i, j
                if len(self.table[i].slots[0]) is 0:
                    return i, j
        # Should never get here
        raise Exception('Ran out of overflow buckets!')


ht = HashTable()

ht.DataIn()

ht.GenerateReport('before.txt')

ht.SaveReport()

if ht.table is not None:
    raise Exception('The hash table must be deleted from memory.')

ht.RestoreReport()

ht.GenerateReport('after.txt')

ht.Search()

# print('{0:20} {1}'.format(' ','hash table'.center))
