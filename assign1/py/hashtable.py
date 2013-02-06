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


class Slot():

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

    #@todo format
    def CollectStatistics(self):
        # Collection avg chain #'s
        # Total length of each primary bucket
        # Avg of all primary buckets
        # Exclude buckets with zero slots
        # For total length, similar to before/after report
        chain = []
        chain_count = {}
        avg_chain = 0
        for i in range(20, 30):
            if self.table[i].overflow is not None:
                chain.append(int(self.table[i].overflow) + 1)
            else:
                chain.append(0)
            if i not in chain_count.keys() and self.table[i].overflow is not None:
                chain_count[int(self.table[i].overflow) + 1] = chain.count(int(self.table[i].overflow) + 1)
                avg_chain += chain_count[int(self.table[i].overflow) + 1]
        avg_chain /= (len(chain_count) + 1)
        print('Average is {0}'.format(avg_chain))

        total_length = 0
        total_length_avg = 0
        non_zero_buckets = 0
        for i in range(0, 20):
            total_length += int(self.table[i].count)
            if int(self.table[i].count) is not 0:
                non_zero_buckets += 1
        total_length_avg = total_length / non_zero_buckets
        print('Total length is {0}'.format(total_length))
        print('Total length avg is {0}'.format(total_length_avg))

    def Search(self):
        f = open('./search.dat', 'r+')
        f2 = open('./retrieval.txt', 'w+')
        f2.write('Search and Retrieval'.center(82))
        f2.write('\n')
        f2.write('Transactions'.center(82))
        f2.write('\n')
        f2.write('Search Key\t\tBucket/Slot\t\tRecord'.center(82))
        f2.write('\n')
        found = False
        for keys in f.readlines():
            key = self.Hash(keys[:10])
            for pos, item in enumerate(self.table):
                for index, slot in enumerate(item.slots):
                    if key in item.slots[index]:
                        if keys[:10] == item.slots[index][key].key:
                            found = True
                            f2.write('{0:>35}{1:>16}/{2}\t\t{3}'.format(
                                item.slots[index][key].key,
                                pos + 1,
                                index + 1,
                                item.slots[index][key].value
                            ))
                            f2.write('\n')
                            # f2.write('{0:>35}{1:>16} {2}\t\t{3}'.format(
                            #     keys[:10],
                            #     ' ',
                            #     ' ',
                            #     'Record not found'
                            # ))
                            # f2.write('\n')
            if found == False:
                f2.write('{0:>35}{1:>16} {2}\t\t{3}'.format(
                    keys[:10],
                    ' ',
                    ' ',
                    'Record not found'
                ))
                f2.write('\n')
        f.close()
        f2.close()

    def RestoreReport(self):
        # Why restore a structure that still exists?
        if self.table is not None:
            raise Exception('The hash table has been restored already.')
        f = open('./hashtable.txt', 'rb+')
        # Loads the file back into memory
        self.table = pickle.load(f)
        f.close()

    def SaveReport(self):
        f = open('./hashtable.txt', 'wb+')
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
            for index, slot in enumerate(item.slots):
                for key, value in item.slots[index].items():
                    if item.slots[index][key] is not None:
                        f.write('\tSlot {0}: {1}{2}\n'.format(index + 1,
                                item.slots[index][key].key,
                                item.slots[index][key].value))
                if len(item.slots[index].keys()) is 0:
                    f.write('\tSlot {0}: None\n'.format(index + 1))
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
            item, index = tup
            if self.table[index].count > 2:
                index = self.CheckAvailableBuckets(key, 20, MaxBuckets)
                # overflow is true
                length = self.table[index].count
                while length == 3:
                    # overflow of overflow is true
                    index = self.CheckAvailableBuckets(key,
                        index + 1, MaxBuckets)
                    length = self.table[index].count
                if length > 0:
                    # insert into 'old' overflow bucket
                    self.table[index].slots[length][key] = Slot()
                    self.table[index].slots[length][key].key = data
                    self.table[index].slots[length][key].value = value
                    self.table[index].count += 1
                    self.SetOverflowPointer(index, key)
                else:
                    # new overflow bucket
                    self.table[index].slots[0][key] = Slot()
                    self.table[index].slots[0][key].key = data
                    self.table[index].slots[0][key].value = value
                    self.table[index].count += 1
                    self.SetOverflowPointer(index, key)
            else:
                # overflow is false, collission still true
                length = self.table[index].count
                self.table[index].slots[length][key] = Slot()
                self.table[index].slots[length][key].key = data
                self.table[index].slots[length][key].value = value
                self.table[index].count += 1
        else:
            #brand new key
            index = self.CheckAvailableBuckets(key, 0, TableSize)
            length = self.table[index].count
            self.table[index].slots[length][key] = Slot()
            self.table[index].slots[length][key].key = data
            self.table[index].slots[length][key].value = value
            self.table[index].count += 1

    def SetOverflowPointer(self, index, key):
        # Sets overflow 'pointer'
        #@todo: have it work for overflow of overflows
        of_index = self.CheckAvailableBuckets(key,
            0, TableSize)
        self.table[index].overflow = of_index
        self.table[of_index].overflow = index

    def CollissionCheck(self, key):
        for pos, item in enumerate(self.table):
            for index, slot in enumerate(item.slots):
                if key in item.slots[index]:
                    # Returns a tuple
                    return slot, pos
        # Returns none if there is no collission
        return None

    def CheckAvailableBuckets(self, key, minimum, maximum):
        for i in range(minimum, maximum):
            for j in range(0, 3):
                if key in self.table[i].slots[j].keys():
                    return i
                if len(self.table[i].slots[0]) is 0:
                    return i
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

ht.CollectStatistics()
