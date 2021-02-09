#Imports random, pickle, pygame and time modules
import random, pickle, pygame, time
#Imports locals for use in adding input
from pygame.locals import *

#Initialize pygame
pygame.init()

#Initialises pygame music mixer
pygame.mixer.init()
#Loads music file
pygame.mixer.music.load('floyd.ogg')
#Plays song indefinitely
pygame.mixer.music.play(-1)

#Set variables for width and height of window
width = 1200
height = 600

#Set colours in variables
black = (0,0,0)
white = (255,255,255)
aqua_blue = (113,221,229)

#Initialise variables
num_ques = 0
used_questions = []
overall_score = 0
song_time = 0

#Create screen in window
screen = pygame.display.set_mode((width,height))
#Set caption of window
pygame.display.set_caption("IQ Test")
#Get clock
clock = pygame.time.Clock()

#Set FPS variable
FPS = 60

#Set variable for FPS clock
playtime = 0.0
ticks = clock.tick(FPS)

#Opens file using name and mode
def open_file(name, mode):
    '''Opens file'''
    #Tries to open file
    try:
        iq_file = open(name, mode)
    #Will print this out if IOError is recieved
    except IOError as e:
        print("The file {0} does not exist.\n{1}".format(name,e))
        input("\n\nPress enter to exit the program. ")
        sys.exit()
    else:
        #Returns trivia_file
        return iq_file
        
#reads next line of the file
def next_line(iq_file):
    '''Reads next line of file'''
    line = iq_file.readline()
    return line

def text_objects(text, font):
    '''Renders text'''
    #Creates surface with rendered text
    textSurface = font.render(text, True, black)
    #Returns surface and rectangle of surface
    return textSurface, textSurface.get_rect()

#Display Text
def display_text(text, width, height, size):
    '''Displays text'''
    #Gets font and size and puts in variable
    size_text = pygame.font.Font("futura.ttf", size)
    #Gets text surface and and rectangle
    TextSurf, TextRect = text_objects(text, size_text)
    #Centers the text in the rectangle
    TextRect.center = ((width),(height))
    #Blits text surface and rectangle
    screen.blit(TextSurf, TextRect)

#Button
def button(x, y, width, height, text, text_width, text_height, text_size, button):
    '''Creates button'''
    #Gets mouse position
    mouse_pos = pygame.mouse.get_pos()
    #Gets whether mouse button has been pressed
    click = pygame.mouse.get_pressed()
    #Draws rectangle for button
    pygame.draw.rect(screen, black, [x, y, width, height], 2)
    #Displays text within button
    display_text(text, text_width, text_height, text_size)
    #Checks if mouse position is within boundaries of button
    if x+width > mouse_pos[0] > x and y+height > mouse_pos[1] > y:
        #Draws the box in aqua blue
        pygame.draw.rect(screen, aqua_blue, [x, y, width, height], 2)
        #If left clicked
        if click[0] == 1:
            #Checks what destination button desires
            #if start
            if button == "s":
                #Resets time
                global time_left
                time_left = 201.0
                #Slight delay so button on next screen isn't accidentally clicked
                time.sleep(0.2)
                #Starts quiz function
                quiz()
            #If menu
            elif button == "m":
                #Delay
                time.sleep(0.2)
                #Starts menu function
                menu()
            #If high scores
            elif button == "hs":
                #Delay
                time.sleep(0.2)
                #Starts high scores function
                high_scores()
            #If correct
            elif button == "c":
                #adds 10 to overall score
                global overall_score
                overall_score = overall_score + 10
                #Delay
                time.sleep(0.2)
                #Starts quiz function
                quiz()
            #If wrong
            elif button == "w":
                #Delay
                time.sleep(0.2)
                #Starts quiz function
                quiz()
            #Pauses music and gets position stopped at
            elif button == "pa":
                pygame.mixer.music.pause()
                global song_time
                song_time = song_time + pygame.mixer.music.get_pos()
            #Plays music from stopped position
            elif button == "pl":
                pygame.mixer.music.play(-1, song_time)
            #If quit
            elif button == "q":
                #Quits pygame then closes window
                pygame.quit()
                quit()


#Maths question       
def maths_question():
    '''Generates math question'''
    #Makes list of operators
    operators = ["*", "/", "+", "-"]
    #Chooses random operator
    operator = random.choice(operators)
    #Generates random numbers for questions
    num1 = random.randint(0, 100)
    num2 = random.randint(0, 100)
    num3 = random.randint(1, 20)
    num4 = random.randint(1, 20)
    #Chooses number to be used as the correct choice
    correct_choice = random.randint(0, 3)
    #Creates a list of random numbers to be used as wrong answers
    wrong_list = []
    for x in range(4):
        wrong = random.randint(0, 200)
        wrong_list.append(wrong)

    #Boolean value for while loop
    math = True
    
    while math:
        
        #Makes time left a float and takes away ticks/1860
        global time_left
        time_left = float(time_left)
        time_left = time_left - ticks/1860.0
        #String slice to get rid of decimals except for last 10 seconds
        if 10 <= time_left < 100:
            display_time = (str(time_left))[0:2]
        else:
            display_time = (str(time_left))[0:3]

        for event in pygame.event.get():
            #Quits game if "X" is clicked
            if event.type == pygame.QUIT:
                pygame.quit()
                quit()

        #Fills screen white
        screen.fill(white)

        #Buttons to pause/play music
        button(((9*width)/10)-200, ((9*height)/10)-25, 100, 50, "Pause", ((9*width)/10)-150, ((9*height)/10), 30, "pa")
        button(((9*width)/10)-50, ((9*height)/10)-25, 100, 50, "Play", ((9*width)/10), ((9*height)/10), 30, "pl")
        
        #Draws black box on screen in left corner for timer
        pygame.draw.rect(screen, black, [(width/10)-50, (height/10)-15, 100, 30], 2)
        #Displays time left in box
        display_text(display_time, (width/10), (height/10), 30)
        #If branch determining question to display depending on the operator chosen
        if operator == "*":
            #Formats question in a string
            question = "What is the result of {0} X {1}?".format(num3,num4)
            #Displays question at top of window
            display_text(question, (width/2), (height/6), 50)
            #Works out correct answer
            correct = num3*num4
        elif operator == "/":
            question = "What is the result of {0} / {1}?".format(num3,num4)
            display_text(question, (width/2), (height/6), 50)
            correct = num3/num4
        elif operator == "+":
            question = "What is the result of {0} + {1}?".format(num1,num2)
            display_text(question, (width/2), (height/6), 50)
            correct = num1+num2
        else:
            question = "What is the result of {0} - {1}?".format(num1,num2)
            display_text(question, (width/2), (height/6), 50)
            correct = num1-num2

        #for each loop creates a button
        for i in range(4):
            #Creates the correct button at correct_choice position and ensures button is correct if wrong answers generate correct answer
            if i == correct_choice or correct in wrong_list:
                answer = "{0}) {1}".format(i+1, correct)
                button((width/2)-150, (height/3)-25+i*100, 300, 50, answer, (width/2), (height/3)+i*100, 30, "c")
            #Creates wrong button at other positions  
            else:
                answer = "{0}) {1}".format(i+1, wrong_list[i])
                button((width/2)-150, (height/3)-25+i*100, 300, 50, answer, (width/2), (height/3)+i*100, 30, "w")
        #updates display every loop
        pygame.display.update()


#Text question
def text_question(iq_file):
    #Resets used questions for every new section out of text sections
    if num_ques == 11 or num_ques == 16 or num_ques == 21 or num_ques == 26 or num_ques == 31:
        global used_questions
        used_questions = []
    #chooses random number for question
    rand_num = random.randint(0,9)
    #Will choose a new number if number already used
    while rand_num in used_questions:
        rand_num = random.randint(0,9)
    #Appends number to used
    used_questions.append(rand_num)
    #Ensures loop starts
    ques_num = -1
    while ques_num != rand_num:
        #Reads question from file and puts in variable
        question = next_line(iq_file)
        #Gets rid of newline char
        if question:
            question = question[:-1]
        #Puts the 4 answers in a list
        answers = []
        for i in range(4):
            answer = next_line(iq_file)
            #Gets rid of newline char
            if answer:
                answer = answer[:-1]
            #Puts answers in a list
            answers.append(answer)
        #Reads correct answer puts in a variable
        correct = next_line(iq_file)
        #Gets rid of newline char
        if correct:
            correct = correct[0]
            correct = int(correct)
        #Reads points from file and puts in variable
        points = next_line(iq_file)
        #Converts to int
        if points:
            points = int(points)
        #Adds one to ques_num
        ques_num += 1
    #Resets file back to first line
    iq_file.seek(0)
    #Prints question and answers

    #Sets up True value for loop
    text = True
    
    while text:
        
        global time_left
        time_left = float(time_left)
        #Makes time left a float and takes away ticks/1860
        time_left = time_left - ticks/1860.0
        
        #String slicing to get rid of decimals except for last 10 seconds
        if 10 <= time_left < 100:
            display_time = (str(time_left))[0:2]
        else:
            display_time = (str(time_left))[0:3]

        #Will call time out function if time_left is less than or equal to 0
        if time_left <= 0:
            time_out()
            
        for event in pygame.event.get():
            #Will quit if "X" is pressed
            if event.type == pygame.QUIT:
                pygame.quit()
                quit()

        #Fills screen with white        
        screen.fill(white)

        #Buttons to pause/play music
        button(((9*width)/10)-200, ((9*height)/10)-25, 100, 50, "Pause", ((9*width)/10)-150, ((9*height)/10), 30, "pa")
        button(((9*width)/10)-50, ((9*height)/10)-25, 100, 50, "Play", ((9*width)/10), ((9*height)/10), 30, "pl")
        
        #Draws rectangle for timer
        pygame.draw.rect(screen, black, [(width/10)-50, (height/10)-15, 100, 30], 2)
        #Displays timer in box
        display_text(display_time, (width/10), (height/10), 30)
        #Displays question at top of window size 50 text
        display_text(question, (width/2), (height/6), 50)
        
        #Loops 4 times
        for y in range(len(answers)):
            #Puts answer from list in string
            answer = "{0}) {1}".format(y+1, answers[y])
            #If loops to correct answer of question then button created with correct answer
            if (y+1) == correct:
                button((width/2)-150, (height/3)-25+y*100, 300, 50, answer, (width/2), (height/3)+y*100, 30, "c")
            #Else wrong button created with wrong answers
            else:
                button((width/2)-150, (height/3)-25+y*100, 300, 50, answer, (width/2), (height/3)+y*100, 30, "w")

        #Updates display
        pygame.display.update()

#Out of time function
def time_out():
    '''Tells user they have run out of time'''

    #Sets boolean value to true for loop
    time = True
    
    while time:
        
        for event in pygame.event.get():
            #Quits game if "X" pressed
            if event.type == pygame.QUIT:
                pygame.quit()
                quit()

        #Screen filled with white
        screen.fill(white)
        #Puts message in string
        message = "You ran out of time"
        #Displays message at top of window size 100
        display_text(message, (width/2), (height/5), 100)
        #Creates menu button allows you to go back to menu and restart
        button((width/2)-100, (height/2)-25, 200, 50, "Menu", (width/2), (height/2), 30, "m")

        #Updates display
        pygame.display.update()

#User name function              
def user_name():
    '''Asks for users name'''

    #Creates empty string
    string = ""
    #Question to be used put in string
    name_ques = "What is your name?"
    error = "You need to enter a name."
    #Error false
    is_error = False
    
    user_input = True

    while user_input:
        
        for event in pygame.event.get():
            #Quits if "X" is pressed
            if event.type == pygame.QUIT:
                pygame.quit()
                quit()
                
            #Checks if key has been pressed
            elif event.type == KEYDOWN:
                
                #Checks if key unicode was a letter
                if event.unicode.isalpha():
                    #Adds letter to string
                    string += event.unicode
                #Checks if key was a backspace
                elif event.key == K_BACKSPACE:
                    #Takes last letter from string
                    string = string[:-1]
                #Checks if enter key is pressed
                elif event.key == K_RETURN:
                    #Checks if string is still empty when enter key pressed
                    if string == "":
                        #Error true
                        is_error = True
                    else:
                        #Else return string
                        return string

        #Screen filled white    
        screen.fill(white)
        #If error true displays error message
        if is_error:
            display_text(error, (width/2), ((3*height)/4), 60)
        #Displays question asking user to enter name
        display_text(name_ques, (width/2), (height/4), 75)
        #Displays name as its being typed
        display_text(string, (width/2), (height/2), 50)
        #Updates display
        pygame.display.update()

#Updates high scores
def update_high_scores(iq, time):
    '''Adds the new score along with time taken'''
    
    #Calls user name function and returns name
    name = user_name()
    #Creates list with name, iq and time taken
    high_score = [name, iq, time]
    
    #High scores file opened for appending to
    high_file = open_file("high_scores.dat", "ab")
    #list pickled to file
    pickle.dump(high_score, high_file)
    #file closed
    high_file.close()
    
    #Returns name
    return name


#High scores function
def high_scores():
    '''Displays High Scores screen'''
    #Creates empty list for high scores
    high_scores = []
    #Opens file for reading
    high_file = open_file("high_scores.dat", "rb")
    
    #Loops through file until empty line
    try:
        while True:
            #reads line
            high_line = pickle.load(high_file)
            #Appends line to list
            high_scores.append(high_line)
    except EOFError:
        pass
    #Closes file
    high_file.close()
    #Sorts list first in decreasing order of score then increasing order of time
    high_scores.sort(key=lambda x: (int(-(x[1])),x[2]))
    #Message in string
    score_message = "The top 10 high scores are:"
    
    high_score = True
    
    while high_score:
        
        for event in pygame.event.get():
            #Quits game if "X" pressed
            if event.type == pygame.QUIT:
                pygame.quit()
                quit()

        #Screened filled white
        screen.fill(white)

        #Buttons to pause/play music
        button(((9*width)/10)-200, ((9*height)/10)-25, 100, 50, "Pause", ((9*width)/10)-150, ((9*height)/10), 30, "pa")
        button(((9*width)/10)-50, ((9*height)/10)-25, 100, 50, "Play", ((9*width)/10), ((9*height)/10), 30, "pl")
        
        #Displays message
        display_text(score_message, (width/2), (height/8), 50)

        #If list longer or equal to 10 scores then only first 10 displayed
        if len(high_scores) >= 10:
            for i in range(10):
                score = "{0}. {1} - {2} - {3} seconds".format(i+1, high_scores[i][0], high_scores[i][1], high_scores[i][2])
                display_text(score, (width/2), (height/4)+i*35, 30)
        #If less than ten but still 1 or more then only that amount is displayed
        elif 1 <= len(high_scores) < 10:
            for i in range(len(high_scores)):
                score = "{0}. {1} - {2} - {3} seconds".format(i+1, high_scores[i][0], high_scores[i][1], high_scores[i][2])
                display_text(score, (width/2), (height/4)+i*35, 30)
        #Otherwise "None" is displayed
        else:
            display_text("None", (width/2), (height/4), 30)

        #Creates back and quit buttons
        button((width/4)-100, (height/2)-25, 200, 50, "Back", (width/4), (height/2), 30, "m")
        button(((3*width)/4)-100, (height/2)-25, 200, 50, "Quit", ((3*width)/4), (height/2), 30, "q")

        #Updates display
        pygame.display.update()


#quiz
def quiz():
    '''Main function controlling quiz'''

    #Declare as global variable
    global num_ques
    
    #First 5 questions are maths based
    if num_ques < 5:
        #Adding one to number of questions
        num_ques = num_ques + 1
        #Displays maths question with answers
        maths_question()
    
    #Rest are text based with different sections 5 questions long
    elif 5 <= num_ques < 10:
        #General knowledge questions
        iq_file = open_file("general knowledge.txt", "r")
        num_ques = num_ques + 1
        #Display a text question with answers
        text_question(iq_file)
        
    elif 10 <= num_ques < 15:
        #Music questions
        iq_file = open_file("music.txt", "r")
        num_ques = num_ques + 1
        text_question(iq_file)
        
    elif 15 <= num_ques < 20:
        #Movie questions
        iq_file = open_file("movies.txt", "r")
        num_ques = num_ques + 1
        text_question(iq_file)
        
    elif 20 <= num_ques < 25:
        #Geography questions
        iq_file = open_file("geography.txt", "r")
        num_ques = num_ques + 1
        text_question(iq_file)
        
    elif 25 <= num_ques < 30:
        #Language questions
        iq_file = open_file("language.txt", "r")
        num_ques = num_ques + 1
        text_question(iq_file)

    #Else the quiz has finished
    else:
        #Converts score to IQ
        global overall_score
        iq = int(overall_score*(2/3))
        #Resets score for next time
        overall_score = 0
        #Works out time taken to complete test
        global time_left
        time_left = int(time_left)
        time = 200-time_left
        #Adds name, score and time to file and returns name
        name = update_high_scores(iq, time)
        #Resets number of questions
        num_ques = 0
        
        quiz = True
        while quiz:
            
            for event in pygame.event.get():
                #Quits if "X" is pressed
                if event.type == pygame.QUIT:
                    pygame.quit()
                    quit()

            #Screen filled with white
            screen.fill(white)

            #Buttons to pause/play music
            button(((9*width)/10)-200, ((9*height)/10)-25, 100, 50, "Pause", ((9*width)/10)-150, ((9*height)/10), 30, "pa")
            button(((9*width)/10)-50, ((9*height)/10)-25, 100, 50, "Play", ((9*width)/10), ((9*height)/10), 30, "pl")

            #Score, time and play again message to inform user of their achievements
            score_message = "Congratulations {0}! You got an IQ of {1}!".format(name,iq)
            time_message = "And did it in a time of {0} seconds!".format(time)
            play_again = "What would you like to do?"

            #Displays score, time and play again messages
            display_text(score_message, (width/2), (height/6), 50)
            display_text(time_message, (width/2), (height/6)+75, 50)
            display_text(play_again, (width/2), (height/3)+100, 40)

            #Displays buttons to retake test, go to main menu and quit
            button((width/4)-100, ((2*height)/3)-25, 200, 50, "Retake Test", (width/4), ((2*height)/3), 30, "s")
            button((width/2)-100, ((2*height)/3)-25, 200, 50, "Main Menu", (width/2), ((2*height)/3), 30, "m")
            button(((3*width)/4)-100, ((2*height)/3)-25, 200, 50, "Quit", ((3*width)/4), ((2*height)/3), 30, "q")

            #Updates display
            pygame.display.update()


#menu
def menu():
    
    menu = True

    while menu:
        for event in pygame.event.get():
            #Quits if "X" pressed
            if event.type == pygame.QUIT:
                pygame.quit()
                quit()

        #Screen filled white
        screen.fill(white)
        #Displays title for menu
        display_text("IQ Test", (width/2), (height/6), 100)

        #Buttons for pause/play music
        button(((9*width)/10)-200, ((9*height)/10)-25, 100, 50, "Pause", ((9*width)/10)-150, ((9*height)/10), 30, "pa")
        button(((9*width)/10)-50, ((9*height)/10)-25, 100, 50, "Play", ((9*width)/10), ((9*height)/10), 30, "pl")

        #Buttons for Start, High Scores and Quit 
        button((width/2)-100, height/3, 200, 50, "Start", (width/2), (height/3)+25, 30, "s")
        button((width/2)-100, (height/3)+100, 200, 50, "High Scores", (width/2), (height/3)+125, 30, "hs")
        button((width/2)-100, (height/3)+200, 200, 50, "Quit", (width/2), (height/3)+225, 30, "q")

        #Updates display 
        pygame.display.update()

#Start program
menu()


    
    
