﻿#!/usr/bin/env python3
# -*- coding: utf-8 -*-

#import necessary libraries
import wikipedia
from sklearn.feature_extraction.text import TfidfVectorizer
from sklearn.metrics.pairwise import cosine_similarity
import matplotlib.pyplot as plt
import matplotlib.image as mpimg
import nltk
import csv
import string
from nltk.corpus import stopwords as stop_words
import aiml


kernel = aiml.Kernel() # Create a Kernel object. No string encoding (all I/O is unicode)
kernel.setTextEncoding(None)
# Use the Kernel's bootstrap() method to initialize the Kernel. The
# optional learnFiles argument is a file (or list of files) to load.
# The optional commands argument is a command (or list of commands)
# to run after the files are loaded.
# The optional brainFile argument specifies a brain file to load.
kernel.bootstrap(learnFiles="myTVBot-rules.xml")

lemma = nltk.stem.WordNetLemmatizer() #Initialise Lemmatiser from NLTK library

removePunctDict = dict((ord(punct), None) for punct in string.punctuation)
#Dictionary of all punct in string.punctuation with Unicode value None

#Open/read CSV files
def readCSV():
    with open("TVBotQA.csv") as csvFile: #Open CSV file
    #Works if the file is in the same folder, 
    # Otherwise include the full path
        reader = csv.DictReader(csvFile) #Initialise CSV reader

        questCSV = "" #Create list for questions and answers
        ansCSV = []

        for row in reader: #Loop through rows
            questCSV += row["Questions"]+" " #add questions and answers to 
            ansCSV.append(row["Answers"])    #respective lists

        loweredQ = questCSV.lower()# converts to lowercase
        sentTokens = nltk.sent_tokenize(loweredQ) #converts to list of sentences 
        wordTokens = nltk.word_tokenize(loweredQ) #Converts to list of words
        
        return sentTokens, wordTokens, ansCSV #return tokens and answers list

        
#Lemmatises tokens
def lemmaTokens(tokens):
    return [lemma.lemmatize(token) for token in tokens] #Lemmatises each token in tokens

#Removes punctuation from lemmatised words
def lemmaCleaned(data):
    return lemmaTokens(nltk.word_tokenize(data.lower().translate(removePunctDict)))
    #returns tokenised words that have had punctuation removed and lower case applied

#Handles chatbot for similarity based responses
def responseCSV(userResponse, sentTokens, ansCSV):
    chatbotResponse = '' #Initial response from bot
    
    tfidfVec = TfidfVectorizer(tokenizer = lemmaCleaned, stop_words = ['the', 'me', 'i', 'we', 'you', 'and', 'he', 'her'] )
    #Combines CountVectorizer and TfidfTransform to create bag of words excluding stop words
    
    tfidf = tfidfVec.fit_transform(sentTokens) #Combines fit() and transform()
    vals = cosine_similarity(tfidf[-1], tfidf) #find cosine similarity between arguments
    index = vals.argsort()[0][-2] #performs an indirect sort 
    flat = vals.flatten() #Flattens vals array
    flat.sort() #Performs sort
    reqTfidf = flat[-2] #Finds value at position -2
    if(reqTfidf == 0): #No similarity
        chatbotResponse = chatbotResponse + "I am sorry! I don't understand you"
        return chatbotResponse
    else: #return similar response
        chatbotResponse = chatbotResponse + ansCSV[index]
        return chatbotResponse

#main 
def main():
    
    print("Chatbot: Welcome to this TV shows chat bot. Please feel free to ask questions from me!") #Introduce
    #start loop to keep getting user input after bot response
    while True:
        #get user input
        try:
            userInput = input("> ") #Indication for user to input
        except (KeyboardInterrupt, EOFError) as e: #If no input or error then bot wi
            print("Chatbot: Bye!")
            break
        #pre-process user input and determine response agent (if needed)
        responseAgent = 'aiml'
        #activate selected response agent
        if responseAgent == 'aiml':
            answer = kernel.respond(userInput)
        #post-process the answer for commands
        if answer[0] == '#':
            params = answer[1:].split('$') #Will split string either side of the $
            cmd = int(params[0])
            if cmd == 0: #index for standard responses
                print("Chatbot: " + params[1])
                break
            
            elif cmd == 1: #Index for wikipedia api search
                try: #Will try to search
                    wSummary = wikipedia.summary(params[1], sentences=3,auto_suggest=False)
                    print(wSummary)
                except: #Otherwise prints error message
                    print("Chatbot: Sorry, I do not know that. Be more specific!")
            
            elif cmd == 2: #Index to display image using matplotlib
                img = mpimg.imread('twoandahalf.jpg')
                imgplot = plt.imshow(img)
                plt.show()
                print("Chatbot: There you go!")
                
            elif cmd == 99: #Index for similarity-based component
                sentTokens, wordTokens, ansCSV = readCSV() #get tokens and answers from CSV
                sentTokens.append(userInput) #add user input to tokens
                wordTokens = wordTokens + nltk.word_tokenize(userInput) #add user input to work tokens
                print("Chatbot: ", end = "") #Print first part of response
                print(responseCSV(userInput, sentTokens, ansCSV)) #Print chatbot response
                sentTokens.remove(userInput) #Remove user's input from the sent tokens list
                
        else: #Otherwises prints normal response
            print("Chatbot: " + answer)

main() #Call main
