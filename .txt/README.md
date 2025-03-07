# SSRL-ASCII-Encoder/Decoder

This is the Project for round 3 of the SSRL Interviews.



COMMANDS TO USE TO RUN:
    1. make clean (cleans all past outputs)
    2. make (compiles all files into bin)
    3. make run (runs the files)

    
Design Decisions:
    - I decided to use encoding by LSB to encode the desired message, as this would very minmally change the 
    - look of the image, and would be easy to pull the message from. I also decided to use a key, or a special set of
    - characters to designate where the message ends. As per error handling, I decided to use a checksum, as it is lightweight,
    - and easy to encode/decode from the actual message. For this project, I used the stbImage library, as it is one of the easiest and
    - straightforward libraries to use. My program works by first getting the user's input for what message they would like to encode. 
    - It then converts that image, as well as a predetermined key, into binary. Then, my program also take the raw image data from the
    - desired data (using stbImage), and converts that to binary as well. It then encodes a message by changing the last bit for every byte into the
    - Binary ASCII representation of the messasge + key. Furthermore, the checksum is also calculated and added to this encoded section, directly after 
    - the key. Then, the binary data is converted back to raw image/RBG data, anad uploaed as outputImage.png, which looks identical to the original
    - image. As for Decoding, the first step is to convert the raw image data back into binary, and then reading the last bit for each byte starting at 
    - first, in which it appends those bytes into a seprate buffer. The decoder checks each byte to see if it matches the bytes for the key, and when it
    - does, it stops reading, and ends the message. As a final check to see if there are no data errors, the decoder reads the checksum from the message
    - it just decoded, and reads the checksum from the bits of the encoded part of the image, and sees if they are equal. If they are, ther is no data - - lost, and if not, then there is.
    IF ANY MORE CLARIFICATION IS NEEDED ON HOW I APPROACHED THIS PROJECT/HOW IT WORKS, PLEASE LET ME KNOW
    Aryan Dhabale
    811-512-855
    ard37097@uga.edu

Here is the project description: 

This project will involve encoding an ASCII message in a PNG image without (noticeably)
visually altering the image. You may choose the method by which you encrypt your data, but
make a conscious effort to develop an efficient encoding method (how much text data can you
pack in a single image?) and you may not utilize the metadata of the PNG to store information.
The message may be one of your choosing, and the PNG image with which you will be working
is attached alongside this document to the email you received.

The project will be written in the C language, and your project should consist of two separate
programs, one to encode the data in the image, and another to decode the data from the image.
You will need to include a makefile such that a user can run "make clean" and "make" in the
target directory and successfully compile your code. You will also include a README.md file in
which you will describe how your projects work, as well as why you made certain design
decisions (such as choice of encoding method, choice of data redundancy, etc.). You may use a
PNG library of your choosing but be sure to justify your choice in your README. It is alright if
your program is not cross-platform, but please include any necessary libraries for compilation
and include which platform your program was tested on (Windows, Linux, MacOS).
Your program must include some way for the decoder to detect any errors during transmission
in the encoded data. (Bonus points if you implement an error correction method, but this is not
required). Below is a more succinct list of engineering requirements for you to refer to:
Engineering Requirements:
● Must be written in C language. 
● Must include an encoder and decoder program.
● Programs must be able to be compiled by running "make clean" and "make" in the target
directory.
● You may use any PNG library of your choice but justify why you chose what you did.
● The program MAY NOT utilize image metadata to encode the message.
● The message may be of your choosing but must be ASCII (plain text) data. You must
utilize the provided PNG image for testing, but theoretically your method should work for
any PNG file.
● Your program must include a way for the decoder to detect errors, bonus points if the
decoder can correct errors.