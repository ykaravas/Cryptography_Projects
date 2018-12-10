import random
import math
import sys
import os
from BBS import BlumBlumShub
from BBS import millerRabin


######## HELPER CLASSES ########

class public_key(object):
	def __init__(self, group_n = None, prim_root = None, prim_rt_exp_priv = None, num_bits = 0):
		self.group_n = group_n
		self.prim_root = prim_root
		self.prim_rt_exp_priv = prim_rt_exp_priv
		self.num_bits = num_bits

class private_key(object):
	def __init__(self, group_n = None, prim_root = None, priv_num = None, num_bits = 0):
		self.group_n = group_n
		self.prim_root = prim_root
		self.priv_num = priv_num
		self.num_bits = num_bits


######## HELPER FUNCTIONS ########

def modularExp(base, exp, modulus):
	return pow(base, exp, modulus)

	
def fastModular(base,exp,mod):
    b = base
    e = exp
    fin = 1
    while e > 0:
        if e % 2 == 0:
            b = (b * b) % mod
            e = e/2
        else:
            fin = (b * fin) % mod
            e = e - 1
    return fin
	

def calcNumBits(prime_num):
    return math.ceil(math.log(prime_num, 2))


# def isPrime(num):
# 	if ((num == 2) or (num == 3)):
# 		return True
# 	if (((num % 2) == 0) or (num < 2)):
# 		return False
# 	for i in range(3, int(num ** 0.5) + 1, 2):
# 		if ((num % i) == 0):
# 			return False    
			
# 	return True


def getSecret(pubkey, own_privkey):
	group_n = pubkey.group_n
	secret_key = fastModular(pubkey.prim_rt_exp_priv, own_privkey.priv_num, group_n)
	return secret_key


def getMultInv(pubkey, own_privkey):
	group_n = pubkey.group_n
	secret_key = getSecret(pubkey, own_privkey)
	secret_key_inv = pow(secret_key, group_n - 2, group_n)
	return secret_key_inv

def gcd(a, b):
	while b != 0:
		c = a % b
		a = b
		b = c
	#a is returned if b == 0
	return a


def findPrimitiveRoot(num):
    	
 	temp1 = 2
 	temp2 = (num - 1) // temp1

 	if num == 2:
 		return 1

 	while(1):
 		possible_prim_root = random.randint( 2, num-1 )
 		if not (fastModular(possible_prim_root, (num-1) // temp1, num) == 1):
 			if not (fastModular(possible_prim_root, (num-1) // temp2, num) == 1):
 				return possible_prim_root

			
######## HELPER I/O FUNCTIONS ########

def readKeyOrMsg(filename, filetype):

	f = open(filename,'r') 
	file_str = f.read()
	if filetype == "priv":
		key_array = file_str.split(',')
		key_obj = private_key(int(key_array[0]), int(key_array[1]), int(key_array[2]), calcNumBits(int(key_array[0])))
		f.close()
		return key_obj
	elif filetype == "pub":
		key_array = file_str.split(',')
		key_obj = public_key(int(key_array[0]), int(key_array[1]), int(key_array[2]), calcNumBits(int(key_array[0])))
		f.close()
		return key_obj
	else:
		f.close()
		return file_str


def writeKeyOrMsg(filename, filetype, key = None, msg = None):
    
	f = open(filename,'w') 
	if filetype == "priv":
		f.write("{group_n},{prim_root},{priv_num}".format(group_n = key.group_n, prim_root = key.prim_root, priv_num = key.priv_num))
	elif filetype == "pub":
		f.write("{group_n},{prim_root},{prim_rt_exp_priv}".format(group_n = key.group_n, prim_root = key.prim_root, prim_rt_exp_priv = key.prim_rt_exp_priv))
	elif filetype == "msg":
		f.write(msg)
	f.close()
    

def displayOptions():
	print("               MAIN PROGRAM FUNCTIONALITY & COMMAND LINE OPTIONS:")
	print("---------------------------------------------------------------------------------\n")
	print("		  gen  		This will prompt user for number of bits for large prime.")
	print("		  enc  		Alice will encrypt original_msg.txt in her directory")
	print("		  dec   	Bob will decrypt the message previously encrypted by Alice")
	print("		  eve   	Eve will simulate MITM attack by taking Alice's Public key")
	print("		        	and encrypted message and cracking them.")
	print("		  msg   	to change message in 'Generated_Files/Alice/original_msg.txt' file.")
	print("		purge   	to remove all files except original_msg.txt and primes.txt")
	print("		 exit   	to terminate program\n\n\n")
	print("                             AUXILIARY FUNCTIONS")
	print("---------------------------------------------------------------------------------\n")
	print("		  gcd   	to find gcd of two numbers")
	print("		prime   	to find if a number is prime or not")
	print("		modexp  	to perform fast exponentiation\n")



def cleanFiles():
	if os.path.exists(os.path.join("Generated_Files", "Bob", "my_private_key.txt")):
		os.remove(os.path.join("Generated_Files", "Bob", "my_private_key.txt"))
	if os.path.exists(os.path.join("Generated_Files", "Bob", "my_public_key.txt")):
		os.remove(os.path.join("Generated_Files", "Bob", "my_public_key.txt"))
	if os.path.exists(os.path.join("Generated_Files", "Bob", "decrypted_msg.txt")):
		os.remove(os.path.join("Generated_Files", "Bob", "decrypted_msg.txt"))
	if os.path.exists(os.path.join("Generated_Files", "Alice", "my_public_key.txt")):
		os.remove(os.path.join("Generated_Files", "Alice", "my_public_key.txt"))
	if os.path.exists(os.path.join("Generated_Files", "Alice", "my_private_key.txt")):
		os.remove(os.path.join("Generated_Files", "Alice", "my_private_key.txt"))
	if os.path.exists(os.path.join("Generated_Files", "Alice", "encrypted_msg.txt")):
		os.remove(os.path.join("Generated_Files", "Alice", "encrypted_msg.txt"))
	if os.path.exists(os.path.join("Generated_Files", "Eve", "cracked_private_key.txt")):
		os.remove(os.path.join("Generated_Files", "Eve", "cracked_private_key.txt"))
	if os.path.exists(os.path.join("Generated_Files", "Eve", "decrypted_intercepted_msg.txt")):
		os.remove(os.path.join("Generated_Files", "Eve", "decrypted_intercepted_msg.txt"))
	print("\nTXT FILES IN ACTORS DIRECTORIES CLEANED\n")


######## CORE FUNCTIONS ########

# Convert bytes of message to ints in order to encrypt.
def convertBytes2Ints(msg, num_bits):
	
	bytes_in = bytearray(msg, 'utf-16')
	ret = []

	# Converted ints are a linear combination of k message bytes
	x = num_bits // 8

	b = -1 * x
	num = 0
	for i in range(len(bytes_in)):
		if ((i % x) == 0):
			b += x
			num = 0
			ret.append(0)
		temp = bytes_in[i] * (2 ** (8 * (i % x)))
		ret[b // x] += temp
		
	return ret


# Convert ints back to bytes
def convertInts2Bytes(msg, num_bits):

	bytes_out = []

	x = num_bits // 8

	for num in msg:
		for i in range(x):
			temp = num
			for j in range(i + 1, x):
				temp = temp % (2 ** (8 * j))
			next_char = temp // (2 ** (8 * i))
			bytes_out.append(next_char)
			num = num - (next_char * (2 ** (8 * i)))

	converted_msg = bytearray(y for y in bytes_out).decode('utf-16', 'ignore')

	return converted_msg


# Generate pub and priv keys.
def generateKeys(large_prime, bbs, published_prim_root = 0):
	num_bits = calcNumBits(large_prime)
	prim_root = 0

	# Alice is generating key here and hasnt published yet.
	if published_prim_root == 0:
		prim_root = findPrimitiveRoot(large_prime)
		prim_root = fastModular(prim_root, 2, large_prime)
	# Alice has published and Bob will use that primitive root as well.
	else:
		prim_root = published_prim_root

	priv_num = bbs.next(num_bits) 
	prim_rt_exp_priv = fastModular(prim_root, priv_num, large_prime)

	pub_key = public_key(large_prime, prim_root, prim_rt_exp_priv, num_bits)
	priv_key = private_key(large_prime, prim_root, priv_num, num_bits)

	return {'public_key': pub_key, 'private_key': priv_key}

	
# Encrypts using receivers pubkey.prim_rt_exp_priv and
# senders privkey to create shared secret key and encrypt.
def encrypt(pubkey, privkey, plain_text):
    
	# Calculate shared secret key.
	secret = getSecret(pubkey, privkey)
	encrypted_str = ""
	z = convertBytes2Ints(plain_text, privkey.num_bits)

	cipher = []
	for i in z:
		d = (i * secret) % pubkey.group_n
		cipher.append(d)
	
	for obj in cipher:
		encrypted_str += str(obj) + ' '

	return encrypted_str


# Decryption using senders pubkey.prim_rt_exp_priv and 
# receivers privkey to create shared secret key multiplicative
# inverse and decrypt.
def decrypt(pubkey, privkey, cipher):
    # Calculate Multiplicative Inverse of shared secret key.
	secret_inv = getMultInv(pubkey, privkey)
	plain_text = []
	cipher_array = cipher.split()
	for obj in cipher_array:
		d = int(obj)
		plain = (d * secret_inv) % pubkey.group_n
		plain_text.append(plain)

	decrypted_text = convertInts2Bytes(plain_text, privkey.num_bits)
	decrypted_text = "".join([ch for ch in decrypted_text if ch != '\x00'])

	return decrypted_text


def bigStepLittleStep(prime_group, prim_root, prim_rt_exp_priv):

	N = math.ceil(math.sqrt(prime_group - 1)) 

	tbl = {pow(prim_root, i, prime_group):i for i in range(N)}

	c = pow(prim_root, N * (prime_group - 2), prime_group)

	for j in range(N):
		y = (prim_rt_exp_priv * pow(c, j, prime_group)) % prime_group
		if y in tbl: 
			return j * N + tbl[y]

	# Solution not found
	return None


######## MAIN WORKER FUNCTION ########

def run():
	# Alice chooses large prime, publishes key. Alice sends encrypted
	# to Bob using their shared secret key from their DHKE
	# Bob gets Alice's public key computes his own public key. Bob 
	# decrypts messages received by alice using the shared secret key.
	# Eve intercepts public key and encrypted messages and cracks them.
	while(1):
		# Generate keys and exchange.
		displayOptions()	
		command = input('Enter Desired Command: ')
		command = command.replace(" ", "")
		if command == "gen":
			num_bits = input('Enter Number of bits: ')
			# User input of large prime.
			inputs = True
			while(inputs):
				if (int(num_bits) % 2 != 0) or int(num_bits) < 20:
					print("\nNumber of bits was either odd or not larger than 20.\n")
					num_bits = input('Enter Number of bits: ')
				else:
					inputs = False
					
			BBS = BlumBlumShub(int(num_bits))
			large_prime = BBS.next(int(num_bits))

			print("\nPRIME CHOSEN: {0}\n".format(large_prime))
			# ALICE Generates her keys.gen

			# Generate keys.
			alice_keys = generateKeys(large_prime, BBS)
			alice_priv = alice_keys['private_key']
			alice_pub = alice_keys['public_key']

			# Save Public and Private keys for Alice.
			writeKeyOrMsg(os.path.join("Generated_Files", "Alice", "my_private_key.txt"), "priv", alice_priv)
			writeKeyOrMsg(os.path.join("Generated_Files", "Alice", "my_public_key.txt"), "pub", alice_pub)

			# BOB Generates his keys.

			# Need Alice's key for her key.prim_root (chosen primitive root).
			alice_pub_key_obj = readKeyOrMsg(os.path.join("Generated_Files", "Alice", "my_public_key.txt"), "pub")

			# Generate Bob's keys with extra arguement of Alice's primitive root.
			bob_keys = generateKeys(large_prime, BBS, alice_pub_key_obj.prim_root)
			bob_priv = bob_keys['private_key']
			bob_pub = bob_keys['public_key']

			# Save Public and Private keys for Bob.
			writeKeyOrMsg(os.path.join("Generated_Files", "Bob", "my_private_key.txt"), "priv", bob_priv)
			writeKeyOrMsg(os.path.join("Generated_Files", "Bob", "my_public_key.txt"), "pub", bob_pub)
			print("\nKEY GENERATION SUCCESSFULL\n")

		# Encrypt Message (Alice -> Bob).
		elif command == 'enc':
			
			# Load PlainText Message.
			message = readKeyOrMsg(os.path.join("Generated_Files", "Alice", "original_msg.txt"), "msg")

			# Alice encrypts message to Bob. Will need her private key and Bobs public to generate shared key.
			alice_priv_key_obj = readKeyOrMsg(os.path.join("Generated_Files", "Alice", "my_private_key.txt"), "priv")
			bob_pub_key_obj = readKeyOrMsg(os.path.join("Generated_Files", "Bob", "my_public_key.txt"), "pub")
			encrypted_msg = encrypt(bob_pub_key_obj, alice_priv_key_obj, message)

			writeKeyOrMsg(os.path.join("Generated_Files", "Alice", "encrypted_msg.txt"), "msg", None, encrypted_msg)
			print("\nMESSAGE ENCRYPTION SUCCESSFULL\n")

		# Decrypt Message (Bob <- Alice).
		elif command == 'dec':

			# Read in Encrypted Message.
			encrypted_msg = readKeyOrMsg(os.path.join("Generated_Files", "Alice", "encrypted_msg.txt"), "msg")

			# Read in necessary keys (Alice's public and Bob's private in order to generate shared key).
			bob_priv_key_obj = readKeyOrMsg(os.path.join("Generated_Files", "Bob", "my_private_key.txt"), "priv")
			alice_pub_key_obj = readKeyOrMsg(os.path.join("Generated_Files", "Alice", "my_public_key.txt"), "pub")

			# Bob Decrypts Message.
			plain_text_msg = decrypt(alice_pub_key_obj, bob_priv_key_obj, encrypted_msg)
			writeKeyOrMsg(os.path.join("Generated_Files", "Bob", "decrypted_msg.txt"), "msg", None, plain_text_msg)

			# Check results.
			message = readKeyOrMsg(os.path.join("Generated_Files", "Alice", "original_msg.txt"), "msg")
			print("Orig Message: {0}".format(message))
			print("Decr Message: {0}\n".format(plain_text_msg))
			if plain_text_msg == message:
				print("\nMESSAGE DECRYPTION SUCCESSFULL\n")
			else:
				print("\nMESSAGE DECRYPTION FAILED\n")
		
		# Interception of message by Eve (Public key and Encrypted Message).
		elif command == 'eve':
			bob_pub_key_obj = readKeyOrMsg(os.path.join("Generated_Files", "Bob", "my_public_key.txt"), "pub")
			encrypted_msg = readKeyOrMsg(os.path.join("Generated_Files", "Alice", "encrypted_msg.txt"), "msg")
			result_priv_num = bigStepLittleStep(bob_pub_key_obj.group_n, bob_pub_key_obj.prim_root, bob_pub_key_obj.prim_rt_exp_priv)

			# Save Bob's cracked key.
			bob_cracked_key = private_key(bob_pub_key_obj.group_n, bob_pub_key_obj.prim_root, result_priv_num, calcNumBits(bob_pub_key_obj.group_n))
			writeKeyOrMsg(os.path.join("Generated_Files", "Eve", "cracked_private_key.txt"), "priv", bob_cracked_key)

			# Get Alice's pub key now that we have Alice's private to calculate shared key and decrypt message
			alice_pub_key_obj = readKeyOrMsg(os.path.join("Generated_Files", "Alice", "my_public_key.txt"), "pub")

			# Decrypt message and save.
			plain_text_cracked_msg = decrypt(alice_pub_key_obj, bob_cracked_key, encrypted_msg)
			writeKeyOrMsg(os.path.join("Generated_Files", "Eve", "decrypted_intercepted_msg.txt"), "msg", None, plain_text_cracked_msg)

			# Compare decrypted message against original for testing purposes.
			message = readKeyOrMsg(os.path.join("Generated_Files", "Alice", "original_msg.txt"), "msg")

			print("Orig Message: {0}".format(message))
			print("Crck Message: {0}\n".format(plain_text_cracked_msg))
			if plain_text_cracked_msg == message:
				print("\nMESSAGE INTERCEPTION & DECRYPTION SUCCESSFULL\n")
			else:
				print("\nMESSAGE INTERCEPTION & DECRYPTION FAILED\n")

		# Change message in Generated_Files/Alice/original_msg.txt file.
		elif command == 'msg':
			command = input('Enter New Message: ')
			writeKeyOrMsg(os.path.join("Generated_Files", "Alice", "original_msg.txt"), "msg", None, command)
			print("\nMESSAGE CHANGE SUCCESSFULL\n")

		# Remove all files except Generated_Files/Alice/original_msg.txt and Generated_Files/primes.txt
		elif command == 'purge':
			cleanFiles()
		elif command == 'gcd':
			new_command = input('\nEnter two numbers to get their gcd: ')
			a = new_command.split()
			out = gcd(int(a[0]), int(a[1]))
			print("\nGCD of {0} and {1} is: {2}".format(a[0], a[1], out))
		elif command == 'prime':
			new_command = input('\nEnter number to find out if it is prime: ')
			out = millerRabin(int(new_command),100)
			if out == True:
				print("\n{0} is prime".format(new_command))
			elif out == False:
				print("\n{0} is NOT prime".format(new_command))
		elif command == 'modexp':
			new_command = input('\nEnterthree numbers, base, exponent and modulo to perform modular exponentiation: ')		
			a = new_command.split()
			out = fastModular(int(a[0]), int(a[1]), int(a[2]))
			print("\nOutput from modular exponentiation {0}^{1}*mod{2} is: {3}".format(int(a[0]), int(a[1]), int(a[2]), out))
		elif command == 'exit':
			break
		
		else:
			print("\nInvalid Command: {0}. Please try again\n".format(command))
	return


def main():
    
    # Requires at least Python 3.4
	assert (sys.version_info >= (3,4))
	run()
	print("\nGOODBYE\n")


if __name__== '__main__':
	main()