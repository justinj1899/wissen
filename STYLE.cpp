/**
 * \brief  Style guidelines for code in this project.
 * \author Daniel Collins
 * \date   10-6-2018
 *
 * This source file is part of Wissen.
 * Consequently, it is licensed under the GNU GPLv3.
 * Note: The data is in the US-style. (Month first)
 */

/*
 * This file documents the style guidelines to be used for this project.
 * All source files should have a block comment up top, following the style.
 * All source files should list the purpose of the source file, the author,
 *  and the date authored.
 * Major contributions can lead to the addition of another author below.
 *
 * They must have a notice like the one above licensing them under the GPL.
 */

/* No C++-style comments */
// These comments
/* Are allowed for commentary. Instead, use the classic comment */
/* These comments */
/* To comment code. */

/*
 * You can comment out code either with the C++-style comment (//),
 *  or with an #ifdef 0 #endif-pair
 *
 * Note that one space separates the line-wrapping continuation of the first
 *  line, and this second one, when they are part of the same sentence.
 */

#ifdef 0 /* DISABLED */
code_i_am_commenting_out();
#endif

/* OR: */

// some code;
// other code


/*
 * Block comments look like this.
 * The first and last lines are empty.
 */


/* Describle functions like so: */

/**
 * This comment describes the function and its basic behavior.
 *
 * Additional commentary goes here. Parameters, return values, state changes,
 *  and quirks.
 * Note the double ** above, just like at the comment at the top of the file.
 */
void function(...)
{
	...; /* Commentary on this line. */

	/* Comment explaining intent of the following code: */
	complex_logic;
	complex_logic;
	for (;;) {
		complex_loop;
		...;
	}
}

/* Large and important sections can be prefaced with a comment like this: */
/*********************
 ** SECTION COMMENT **
 *********************/

/*
 * Indentation rules:
 *
 * Source files should use tabs for indentation, spaces for alignment.
 * This is often called "smart tabs."
 * If your editor doesn't support it, @zorodc can use Emacs to fix your code.
 */

/*
 * Code guidelines:
 *
 * Source code lines shouldn't exceed 80 characters often, and if they do,
 *  they should do so only a little bit.
 *
 * Try to keep functions smaller: under 20 lines or so.
 * Most functions should be small, but it is O.K. to have a few bigger ones,
 *  if their logic is simple or clear.
 */

/*
 * Don't nest code too deeply.
 * Try not to go more than 4 indentation levels deep, not counting indentation
 *  from a class/namespace.
 *

/*
 * All header files should use an include guard:
 */

#ifndef HEADER_NAME_HPP
#define HEADER_NAME_HPP

/* Code/definitions */

#endif /* HEADER_NAME_HPP */
