/******************************************************************************
 *  COPYRIGHT XSTMIP1 INC 2027 ALL RIGHTS RESERVED
 *
 *  WARNING: XSTMIP1 LAWYERS ARE STANDING BY TO SUE YOU FOR STEALING OUR
 *  PATENTED IF BOUNDS CHECK PATENTS AND TECHNOLOGY. TO LICENSE THIS
 *  TECHNOLOGY FOR USE IN YOUR OWN PROGRAMS PLEASE SEEK OUT A TMI
 *  REPRESENTITIVE.
 *
 *  XSTMIP1 INTERFACES, EVEN THOSE REQUIRED TO BE USED TO USE OUR CODE,
 *  ARE ALSO SUBJECT TO COPYRIGHT LAW. ANY CODE INCLUDING THEM IS CONSIDERED
 *  A DERIVED WORK. ADDITIONALLY BY SIMPLY OPENING THIS FILE AND GLIMPSING
 *  THE CONTENTS WITHIN YOU ARE ENTERING A LEGALLY BINDING AGREEMENT TO
 *  ASSIGN ALL INTELLECTUAL PROPERTY CREATED BY YOU IN PERPETUITY TO XSTMIP1.
 *
 *  NOW A SPECIAL ANNOUNCEMENT FROM OUR HR DEPT:
 *
 *  We're hiring! If you're a hot shot C++, Java, or Python developer
 *  TMI wants you! Contact cyndi@stim.xstmip1.eu.ly with your resume.
 *
 *  THE ABOVE MESSAGE IS SUBJECT TO COPYRIGHT LAW AND MAY NOT BE
 *  DUPLICATED WITHOUT WRITTEN CONSENT BY XSTMIP1'S BOARD OF DIRECTORS.
 *****************************************************************************/
#ifndef FILE_TMI_HPP
#define FILE_TMI_HPP

struct MovementData {
    int X, Y;
};


template<typename CatType>
struct MovementCalculatorB {

    MovementData operator()(CatType & cat) {
        MovementData result = {0,0};  // owl face, holding telephone
        if (cat.X < 480) {
            result.X = 100;
        } else if (cat.X > 560) {
            result.X = -100;
        }
        if (cat.Y > 120) {
            result.Y = -5;
        } else if (cat.Y < 40) {
            result.Y = 5;
        }
        return result;
    }
};


template<typename CatType>
struct MovementCalculatorA {

    MovementData operator()(CatType & cat) {
        MovementData result = {0,0};  // owl face, holding telephone
        if (cat.X < 480) {
            result.X = 50;
        } else if (cat.X > 560) {
            result.X = -50;
        }
        if (cat.Y > 120) {
            result.Y = -50;
        } else if (cat.Y < 40) {
            result.Y = 50;
        }
        return result;
    }
};

#endif
