// Helper functions for music
//include header files
#include <cs50.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

//include helper functions
#include "helpers.h"

//initialise functions used in function frequency
int no_overlap_get_n_for_lower_notes(int octave, int offset);
int no_overlap_get_n_for_higher_notes(int octave, int offset);
int has_overlap_get_n_for_lower_notes(int octave, int offset);
int has_overlap_get_n_for_higher_notes(int octave, int offset);
int overlap_on_lower_notes_calculate_n(int octave_value, int offset);
int overlap_on_higher_notes_calculate_n(int octave_value, int offset);
int no_overlap_calculate_n(int octave_value, int offset);

// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
    return (atoi(&fraction[0]) * (8 / atoi(&fraction[2])));
}


// Calculates frequency (in Hz) of a note
int frequency(string note)
{
    int frequency = 0;
    int note_string_length = strlen(note);
    
    /* offset is the distance of first 'that note letter' from A4 eg for A4 offset is 0 but for Af4 or A#4 offset is 1 and for A#1
    or Af1 the offset is still 1 */
    int offset = 0;

    //get octave_value from note, eg for D4, octave value is 4 and for F#5 it is 5
    int octave_value = atoi(&note[note_string_length - 1]);
    
    // note alphabet is first character of note string
    int note_alphabet = note[0];
    
    //initialise accidental with empty character
    char accidental= '\0';
    
    // eg accidental is # or b in A#4 or Ab4, while A4 or B5 do not have accidentals
    if(note_string_length > 2)
            {
                accidental = note[note_string_length - 2];
            }
    
    //n is the number of semitone the note is away from A4, eg for Af4 or A#4 n is 1
    int n = 0;
    
    //return code 1 for octave_value not allowed (octave_value allowed here are in the range 1 to 7)
    if (octave_value < 1 || octave_value > 7)
    {
        return 1;
    }

    //switch for note_alphabet, sets value of n(no of semitone the note is away from A4) 
    
    switch (note_alphabet)
    {
        case 'A':
        
            if(accidental)
            {
                if (accidental == '#') //A#
                {
                    //offset is number of semitone from A4, A#4 is 1 semitone away from A4
                    offset = 1;
                    n = overlap_on_lower_notes_calculate_n(octave_value, offset);
               
                }
                else if (accidental == 'b') //Af
                {
                    //offset is number of semitone from A4, Ab4 is 1 semitone away from A4
                    offset = 1;
                    n = overlap_on_higher_notes_calculate_n(octave_value, offset);
                }
            }
         
            else //for natural A notes
            {
                offset = 0;
                n = no_overlap_calculate_n(octave_value, offset);
            }

            break;

        case 'B':
            if(accidental)
            {
                accidental = note[note_string_length - 2];
                
                if (accidental == 'b')
                {
                    //offset is number of semitone from A4, Bb4 is 1 semitone away from A4
                    offset = 1;
                    n = overlap_on_lower_notes_calculate_n(octave_value, offset);
                }
            }
    
            else
            {
                //offset is number of semitone from A4, B4 is 2 semitone away from A4
                offset = 2;
                n = overlap_on_lower_notes_calculate_n(octave_value, offset);
            }

            break;

        case 'C':
            if(accidental)
            {
                if (accidental == '#')
                {
                    //offset is number of semitone from A4, C#4 is 8 semitone away from A4
                    offset = 8;
                    n = overlap_on_higher_notes_calculate_n(octave_value, offset);
                }   
            }

            else
            {
                //offset is number of semitone from A4, C4 is 9 semitone away from A4
                offset = 9;
                n = overlap_on_higher_notes_calculate_n(octave_value, offset);
            }

            break;
            
        case 'D':
            if(accidental)
            {
                if (accidental == '#')
                {
                    //offset is number of semitone from A4, D#4 is 6 semitone away from A4
                    offset = 6;
                    n = overlap_on_higher_notes_calculate_n(octave_value, offset);
                }
                else if (accidental == 'b')
                {
                    //offset is number of semitone from A4, Db4 is 8 semitone away from A4
                    offset = 8;
                    n = overlap_on_higher_notes_calculate_n(octave_value, offset);
                }
            }
    
            else
            {
                //offset is number of semitone from A4, D is 7 semitone away from A4
                offset = 7;
                n = overlap_on_higher_notes_calculate_n(octave_value, offset);
            }

            break;

        case 'E':
            if(accidental)
            {   
                //offset is number of semitone from A4, Eb4 is 6 semitone away from A4
                if (accidental == 'b')
                {
                    offset = 6;
                    n = overlap_on_higher_notes_calculate_n(octave_value, offset);
                }
            }
    
            else
            {
                //offset is number of semitone from A4, E4 is 5 semitone away from A4
                offset = 5;
                n = overlap_on_higher_notes_calculate_n(octave_value, offset);
            }

            break;
            
        case 'F':
            if(accidental)
            {
                //offset is number of semitone from A4, F#4 is 3 semitone away from A4
                if (accidental == '#')
                {
                offset = 3;
                n = overlap_on_higher_notes_calculate_n(octave_value, offset);
                }
            }

            else
            {
                //offset is number of semitone from A4, F4 is 4 semitone away from A4
                offset = 4;
                n = overlap_on_higher_notes_calculate_n(octave_value, offset);
            }

            break;

        case 'G':
            if(accidental)
            {
                if (accidental == '#')
                {
                    //offset is number of semitone from A4, G#4 is 1 semitone away from A4
                    offset = 1;
                    n = overlap_on_higher_notes_calculate_n(octave_value, offset);
                }
                else if (accidental == 'b')
                {
                    //offset is number of semitone from A4, Gb4 is 3 semitone away from A4
                    offset = 3;
                    n = overlap_on_higher_notes_calculate_n(octave_value, offset);
                }
            }
            else
            {
                //offset is number of semitone from A4, G4 is 2 semitone away from A4
                offset = 2;
                n = overlap_on_higher_notes_calculate_n(octave_value, offset);
            }

            break;

        default:
            break;

    }
    
    
    // frequency calculation using formula for various position keys
    
    float exponent_factor = n / 12.;
    
    //if the key is to the right of A4 or is A4 frequency = 2 ^(n/12) * 440
    if ((octave_value == 4) && ((note_alphabet == 'A') || (note_alphabet == 'B')))
    {
        frequency = round(pow(2.0, exponent_factor) * 440);
    }
    
    //if the key is to the left of A4 or is A4 frequency =  440 / 2 ^(n/12)
    else if ((octave_value == 4) && ((note_alphabet == 'C') || (note_alphabet == 'D') || (note_alphabet == 'E') || (note_alphabet == 'F') ||
                                     (note_alphabet == 'G')))
    {
        frequency = round(440 / (pow(2.0, exponent_factor)));
    }
    
    //if the key is to the right of A4 or is A4 frequency = 2 ^(n/12) * 440
    else if ((octave_value > 4))
    {
        frequency = round(pow(2.0, exponent_factor) * 440);
    }
    
    //if the key is to the left of A4 frequency = 440/(2 ^(n/12)
    else if (octave_value < 4)
    {
        frequency = round(440 / (pow(2.0, exponent_factor)));
    }

    return frequency;
}


/*  for overlap on lower notes(have to go through A4 to reach the lower octaves), calls relevant functions to calculate n*/
int overlap_on_lower_notes_calculate_n(int octave_value, int offset)
{
    //if octave_value <=4, or they are lower notes
    if (octave_value <= 4) //eg for A, A4 is first base case , A3 is second base case
    {
        return has_overlap_get_n_for_lower_notes(octave_value, offset);
    }
   
    return no_overlap_get_n_for_higher_notes(octave_value, offset);
    
}


/*  for overlap on higher notes(have to go through A4 to reach the higher octaves), calls relevant functions to calculate n*/
int overlap_on_higher_notes_calculate_n(int octave_value, int offset)
{
    //if octave_value <=4, or they are lower notes    
    if (octave_value <= 4)
    {
        return no_overlap_get_n_for_lower_notes(octave_value, offset);
    }
  
    return has_overlap_get_n_for_higher_notes(octave_value, offset);
   
}

/*  Calls relevant functions to calculate n*/
int no_overlap_calculate_n(int octave_value, int offset)
{
    //if octave_value <=4, or they are lower notes
    if (octave_value <= 4)
    {
        return no_overlap_get_n_for_lower_notes(octave_value, offset);
    }
    
    return no_overlap_get_n_for_higher_notes(octave_value, offset);
    
}


//get n for lower octave(lower than A4), no overlap means there is no going through A4 to reach the lower octave
int no_overlap_get_n_for_lower_notes(int octave, int offset)
{
    if (octave == 4)
    {
        return offset;
    }
    else
    {
        //no of semitones between two octave is 12, adding 12 takes to next octave and calling the recursive function repeats(adds 12) until we get to octave = 4(base case)
        return 12 + no_overlap_get_n_for_lower_notes(octave + 1, offset);
    }
}


//get n for higher octave(higher than A4), no overlap means there is no going through A4 to reach the higher octave
int no_overlap_get_n_for_higher_notes(int octave, int offset)
{
    if (octave == 4)
    {
        return offset;
    }
    else
    {
        //no of semitones between two octave is 12, adding 12 takes to next octave and calling the recursive function repeats(adds 12) until we get to octave = 4(base case)
        return 12 + no_overlap_get_n_for_higher_notes(octave - 1, offset);
    }
}


//get n for lower octave(lower than A4), has overlap means have to go through A4 to reach the lower octave
int has_overlap_get_n_for_lower_notes(int octave, int offset)
{
    if (octave == 4)
    {
        return offset;
    }
    else if (octave == 3)
    {
        return 12 - offset;
    }
    else
    {
        //no of semitones between two octave is 12, adding 12 takes to next octave and calling the recursive function repeats(adds 12) until we get to octave = 4 or 3 (base cases)
        return 12 + has_overlap_get_n_for_lower_notes(octave + 1, offset);
    }
}


//get n for higher octave(higher than A4), has overlap means have to go through A4 to reach the higher octave
int has_overlap_get_n_for_higher_notes(int octave, int offset)
{
    if (octave == 4)
    {
        return offset;
    }
    else if (octave == 5)
    {
        return 12 - offset;
    }
    else
    {
        //no of semitones between two octave is 12, adding 12 takes to next octave and calling the recursive function repeats(adds 12) until we get to octave = 4 or 5(base cases)
        return 12 + has_overlap_get_n_for_higher_notes(octave - 1, offset);
    }
}



// Determines whether a string represents a rest
bool is_rest(string s)
{
    //if the string is empty returns true
    return strcmp(s, "") == 0;
}