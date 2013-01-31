MaxSlots = 3
MaxBuckets = 30
TableSize = 20
OverflowSize = 10


class Bucket:

    def __init__(self):
        self.count = 0
        self.overflow = -1
        self.slots = {}


class HashTable:

    def __init__(self):
        self.table = []
        for i in range(0, MaxBuckets):
            self.table.append(Bucket())

    def ReadFile(self):
        f = open('./datain.dat', 'r')
        for i in f.readlines():
            self.Insert(self.Hash(i[:10]) % TableSize, i[10:])

    def Hash(self, key):
        return ord(key[2]) + ord(key[4]) + ord(key[6]) % TableSize

    def Insert(self, key, value):
        item = self.CollissionCheck(key)
        if item is not None:
            # collission is true
            if 2 in item.keys():
                index = self.CheckAvailableBuckets(key, 19, MaxBuckets)
                # overflow is true
                length = self.GetTableLength(key, index)
                while length == 3:
                    # overflow of overflow is true
                    index = self.CheckAvailableBuckets(key, index + 1,
                        MaxBuckets)
                    length = self.GetTableLength(key, index)
                if length > 0:
                    # insert into 'old' overflow bucket
                    self.table[index].slots[key][length] = value
                else:
                    # new overflow bucket
                    self.table[index].slots[key] = {}
                    self.table[index].slots[key][0] = value
            else:
                length = len(item)
                item[length] = value
                # overflow is false, collission still true
        else:
            #brand new key
            index = self.CheckAvailableBuckets(key, 0, TableSize)
            self.table[index].slots[key] = {}
            self.table[index].slots[key][0] = value

    def GetTableLength(self, key, index):
        if key in self.table[index].slots:
            length = len(self.table[index].slots[key])
        else:
            length = len(self.table[index].slots)
        return length

    def CollissionCheck(self, key):
        for item in self.table:
            if key in item.slots:
                return item.slots[key]
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

ht.ReadFile()

