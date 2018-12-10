import random

def millerRabin(n, k):
    
    l = 0
    d = n-1
    if n == 2 or n == 3:
        return True

    if n % 2 == 0:
        return False

    while d % 2 == 0:
        l += 1
        d //= 2
        
    for i in range(k):
        a = random.randrange(2, n - 1)
        x = pow(a, d, n)
        if x == 1:
            continue
        if x == n - 1:
            continue
        for j in range(l - 1):
            x = pow(x, 2, n)
            if x == n - 1:
                break
        else:
            return False
    return True
    
class BlumBlumShub(object):

    def __init__(self, bits):
      
        self.group_n = self.generateGroupN(bits)
        bit_len = self.calcBits(self.group_n)
        seed = random.getrandbits(bit_len)
        self.state = seed % self.group_n         
    
    def getPrime(self, bits = 0):
        possible_prime = 0
        if(bits == 0):
            possible_prime = random.randint( 2**6, self.group_n - 1)
        else:
            possible_prime = random.randint( 2**6, (2**bits) - 1)
        while True:
            if (possible_prime % 4 == 3) and millerRabin(possible_prime, 100):
                return possible_prime
            possible_prime += 1

    def generateGroupN(self, bits):
        new_bits = bits/2
        p = self.getPrime(new_bits)
        while 1:
            q = self.getPrime(new_bits)
            if p != q:
                return p * q    


    def calcBits(self, b):
        a = 0 

        while b: 
            a += 1 
            b >>= 1 

        return a     

    def next(self, bits):
        
        possible_prime = 0
        while True:
            possible_prime = 0
            for i in range(bits):
                
                self.state = (self.state**2) % self.group_n
            
                possible_prime = (possible_prime << 1) | (self.state & 1)

            if (possible_prime % 4 == 3) and millerRabin(possible_prime, 100):
                return possible_prime
            else:
                continue
            #possible_prime += 1


		