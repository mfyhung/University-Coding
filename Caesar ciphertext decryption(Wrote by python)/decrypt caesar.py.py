#Name: Hung Fan Yan
#SID: 1155083147
#language: python 3.6.4
#Date: 22/3/2018
#IERG4310 Assignment 1
#Get the user input for the encrypted code
encrypted_code = input("Enter your encrypted code:  \n")
encrypted_list = list(encrypted_code)
encrypted_list_fix = list(encrypted_code)
#change the character become the integer
for  i in range (len(encrypted_list)):
    encrypted_list[i] = ord(encrypted_list[i])
for i in range(0 , 25):
    #decrypting
    for j in range(len(encrypted_list)):
        encrypted_list_fix[j] = encrypted_list[j] - i
        if encrypted_list_fix[j] < 97:
            encrypted_list_fix[j] = encrypted_list_fix[j] + 26
    # change the integer back to the character
    for  j in range (len(encrypted_list)):
        if encrypted_list_fix[j] < 97 or encrypted_list_fix[j] > 122:
            encrypted_list_fix[j] = " "
        else:
            encrypted_list_fix[j] = chr(encrypted_list_fix[j])
    #for print out the encrypted code
    print ("when key = ",i,":")
    for j in range (len(encrypted_list)):
        print(encrypted_list_fix[j],end = '')
    print("\n\n")
