# SSRL-ASCII-Encoder/Decoder

This is the Project for round 3 of the SSRL Interviews.

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