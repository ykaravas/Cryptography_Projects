import unittest
import elgamal
from BBS import millerRabin

######## UNIT TEST FUNCTIONS ########

class calcNumBitsTests(unittest.TestCase):
    def test_general(self):
        self.assertEqual(elgamal.calcNumBits(2), 1)
        self.assertEqual(elgamal.calcNumBits(2**32), 32)
        self.assertEqual(elgamal.calcNumBits((2**32) +1), 33)
        self.assertEqual(elgamal.calcNumBits(2**64), 64)
        self.assertEqual(elgamal.calcNumBits(255), 8)
        self.assertEqual(elgamal.calcNumBits(257), 9)   

class isPrimeTests(unittest.TestCase):
    def test_general(self):
        self.assertEqual(millerRabin(2, 100), True)
        self.assertEqual(millerRabin(3, 100), True)
        self.assertEqual(millerRabin(961751663, 100), True)
        self.assertEqual(millerRabin(1000000003273, 100), True)
        self.assertEqual(millerRabin(100000, 100), False)
        self.assertEqual(millerRabin(16, 100), False)
        self.assertEqual(millerRabin(17, 100), True)
        self.assertEqual(millerRabin(29, 100), True)
    
class getMultInvTests(unittest.TestCase):
    def test_general(self):
        pubkey = elgamal.public_key(103,93,23,elgamal.calcNumBits(103))
        privkey = elgamal.private_key(103,93,11,elgamal.calcNumBits(103))
        self.assertEqual(elgamal.getMultInv(pubkey,privkey), 66)

        pubkey = elgamal.public_key(103,91,17,elgamal.calcNumBits(103))
        privkey = elgamal.private_key(103,91,11,elgamal.calcNumBits(103))
        self.assertEqual(elgamal.getMultInv(pubkey,privkey), 50)

        pubkey = elgamal.public_key(1753,391,62,elgamal.calcNumBits(1753))
        privkey = elgamal.private_key(1753,391,1400,elgamal.calcNumBits(1753))
        self.assertEqual(elgamal.getMultInv(pubkey,privkey), 1459)

        pubkey = elgamal.public_key(5791,760,1296,elgamal.calcNumBits(5791))
        privkey = elgamal.private_key(5791,760,5123,elgamal.calcNumBits(5791))
        self.assertEqual(elgamal.getMultInv(pubkey,privkey), 2019)

class encryptDecryptTests(unittest.TestCase):
    def test_general(self):
        
        bob_pubkey = elgamal.public_key(3761,1891,1864,elgamal.calcNumBits(3761))
        alice_privkey = elgamal.private_key(3761,1891,1299,elgamal.calcNumBits(3761))
        alice_pubkey = elgamal.public_key(3761,1891,3478,elgamal.calcNumBits(3761))
        bob_privkey = elgamal.private_key(3761,1891,3722,elgamal.calcNumBits(3761))
        message = "hello how are you"
        encrypted_msg =  elgamal.encrypt(bob_pubkey, alice_privkey, message)
        plain_text_msg = elgamal.decrypt(alice_pubkey, bob_privkey, encrypted_msg)
        self.assertEqual(message, plain_text_msg)

        bob_pubkey = elgamal.public_key(449,322,100,elgamal.calcNumBits(449))
        alice_privkey = elgamal.private_key(449,322,123,elgamal.calcNumBits(449))
        alice_pubkey = elgamal.public_key(449,322,321,elgamal.calcNumBits(449))
        bob_privkey = elgamal.private_key(449,322,122,elgamal.calcNumBits(449))
        message = "jqerbu34 qaqfbiq23   2if892u"
        encrypted_msg = elgamal.encrypt(bob_pubkey, alice_privkey, message)
        plain_text_msg = elgamal.decrypt(alice_pubkey, bob_privkey, encrypted_msg)
        self.assertEqual(message, plain_text_msg)

        bob_pubkey = elgamal.public_key(1753,391,62,elgamal.calcNumBits(1753))
        alice_privkey = elgamal.private_key(1753,391,1400,elgamal.calcNumBits(1753))
        alice_pubkey = elgamal.public_key(1753,391,514,elgamal.calcNumBits(1753))
        bob_privkey = elgamal.private_key(1753,391,999,elgamal.calcNumBits(1753))
        message = "kjbeivb8999 n9u2ewn how are you"
        encrypted_msg =  elgamal.encrypt(bob_pubkey, alice_privkey, message)
        plain_text_msg = elgamal.decrypt(alice_pubkey, bob_privkey, encrypted_msg)
        self.assertEqual(message, plain_text_msg)

        bob_pubkey = elgamal.public_key(5791,760,1277,elgamal.calcNumBits(5791))
        alice_privkey = elgamal.private_key(5791,760,5123,elgamal.calcNumBits(5791))
        alice_pubkey = elgamal.public_key(5791,760,4848,elgamal.calcNumBits(5791))
        bob_privkey = elgamal.private_key(5791,760,4444,elgamal.calcNumBits(5791))
        message = "hello how kn wsijvnij iowenfinwf e9w8u98y23 f9uh29f you"
        encrypted_msg =  elgamal.encrypt(bob_pubkey, alice_privkey, message)
        plain_text_msg = elgamal.decrypt(alice_pubkey, bob_privkey, encrypted_msg)
        self.assertEqual(message, plain_text_msg)
        
class bigStepLittleStepTests(unittest.TestCase):
    def test_general(self):
        priv_num = elgamal.bigStepLittleStep(1753,391,62)
        self.assertEqual(priv_num, 999)
        priv_num = elgamal.bigStepLittleStep(1753,391,514)
        self.assertEqual(priv_num, 1400)
        priv_num = elgamal.bigStepLittleStep(103,91,17)
        self.assertEqual(priv_num, 13)
        priv_num = elgamal.bigStepLittleStep(103,91,18)
        self.assertEqual(priv_num, 11)
        priv_num = elgamal.bigStepLittleStep(103,93,23)
        self.assertEqual(priv_num, 13)
        priv_num = elgamal.bigStepLittleStep(103,93,61)
        self.assertEqual(priv_num, 11)

if __name__ == '__main__':
    unittest.main()
