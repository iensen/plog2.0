// A Bison parser, made by GNU Bison 3.0.4.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.

// Take the name prefix into account.
#define yylex   PlogGrammar_lex

// First part of user declarations.
#line 47 "ploggrammar.yy" // lalr1.cc:404


#include "plog/plogparser.h"
#include "plog/programbuilder.h"
#include <climits>

#define BUILDER (lexer->builder())
#define LOGGER (lexer->logger())
#define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do {                                                               \
        if (N) {                                                       \
            (Current).beginFilename = YYRHSLOC (Rhs, 1).beginFilename; \
            (Current).beginLine     = YYRHSLOC (Rhs, 1).beginLine;     \
            (Current).beginColumn   = YYRHSLOC (Rhs, 1).beginColumn;   \
            (Current).endFilename   = YYRHSLOC (Rhs, N).endFilename;   \
            (Current).endLine       = YYRHSLOC (Rhs, N).endLine;       \
            (Current).endColumn     = YYRHSLOC (Rhs, N).endColumn;     \
        }                                                              \
        else {                                                         \
            (Current).beginFilename = YYRHSLOC (Rhs, 0).endFilename;   \
            (Current).beginLine     = YYRHSLOC (Rhs, 0).endLine;       \
            (Current).beginColumn   = YYRHSLOC (Rhs, 0).endColumn;     \
            (Current).endFilename   = YYRHSLOC (Rhs, 0).endFilename;   \
            (Current).endLine       = YYRHSLOC (Rhs, 0).endLine;       \
            (Current).endColumn     = YYRHSLOC (Rhs, 0).endColumn;     \
        }                                                              \
    }                                                                  \
    while (false)

int PlogGrammar_lex(void *value, Gringo::Location* loc, PlogParser *lexer) {
    return lexer->lex(value, *loc);
}


#line 73 "ploggrammar.tab.cc" // lalr1.cc:404

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "plog/ploggrammar.tab.hh"

// User implementation prologue.

#line 87 "ploggrammar.tab.cc" // lalr1.cc:412
// Unqualified %code blocks.
#line 82 "ploggrammar.yy" // lalr1.cc:413


void PlogGrammar::parser::error(DefaultLocation const &l, std::string const &msg) {
    lexer->parseError(l, msg);
}


#line 97 "ploggrammar.tab.cc" // lalr1.cc:413


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (/*CONSTCOND*/ false)
# endif


// Suppress unused-variable warnings by "using" E.
#define YYUSE(E) ((void) (E))

// Enable debugging if requested.
#if PLOGGRAMMAR_DEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << std::endl;                  \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yystack_print_ ();                \
  } while (false)

#else // !PLOGGRAMMAR_DEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE(Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void>(0)
# define YY_STACK_PRINT()                static_cast<void>(0)

#endif // !PLOGGRAMMAR_DEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 19 "ploggrammar.yy" // lalr1.cc:479
namespace PlogGrammar {
#line 183 "ploggrammar.tab.cc" // lalr1.cc:479

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  parser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr = "";
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              // Fall through.
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }


  /// Build a parser object.
  parser::parser (PlogParser *lexer_yyarg)
    :
#if PLOGGRAMMAR_DEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      lexer (lexer_yyarg)
  {}

  parser::~parser ()
  {}


  /*---------------.
  | Symbol types.  |
  `---------------*/

  inline
  parser::syntax_error::syntax_error (const location_type& l, const std::string& m)
    : std::runtime_error (m)
    , location (l)
  {}

  // basic_symbol.
  template <typename Base>
  inline
  parser::basic_symbol<Base>::basic_symbol ()
    : value ()
  {}

  template <typename Base>
  inline
  parser::basic_symbol<Base>::basic_symbol (const basic_symbol& other)
    : Base (other)
    , value ()
    , location (other.location)
  {
    value = other.value;
  }


  template <typename Base>
  inline
  parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const semantic_type& v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}


  /// Constructor for valueless symbols.
  template <typename Base>
  inline
  parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const location_type& l)
    : Base (t)
    , value ()
    , location (l)
  {}

  template <typename Base>
  inline
  parser::basic_symbol<Base>::~basic_symbol ()
  {
    clear ();
  }

  template <typename Base>
  inline
  void
  parser::basic_symbol<Base>::clear ()
  {
    Base::clear ();
  }

  template <typename Base>
  inline
  bool
  parser::basic_symbol<Base>::empty () const
  {
    return Base::type_get () == empty_symbol;
  }

  template <typename Base>
  inline
  void
  parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move(s);
    value = s.value;
    location = s.location;
  }

  // by_type.
  inline
  parser::by_type::by_type ()
    : type (empty_symbol)
  {}

  inline
  parser::by_type::by_type (const by_type& other)
    : type (other.type)
  {}

  inline
  parser::by_type::by_type (token_type t)
    : type (yytranslate_ (t))
  {}

  inline
  void
  parser::by_type::clear ()
  {
    type = empty_symbol;
  }

  inline
  void
  parser::by_type::move (by_type& that)
  {
    type = that.type;
    that.clear ();
  }

  inline
  int
  parser::by_type::type_get () const
  {
    return type;
  }


  // by_state.
  inline
  parser::by_state::by_state ()
    : state (empty_state)
  {}

  inline
  parser::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  inline
  void
  parser::by_state::clear ()
  {
    state = empty_state;
  }

  inline
  void
  parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  inline
  parser::by_state::by_state (state_type s)
    : state (s)
  {}

  inline
  parser::symbol_number_type
  parser::by_state::type_get () const
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
  }

  inline
  parser::stack_symbol_type::stack_symbol_type ()
  {}


  inline
  parser::stack_symbol_type::stack_symbol_type (state_type s, symbol_type& that)
    : super_type (s, that.location)
  {
    value = that.value;
    // that is emptied.
    that.type = empty_symbol;
  }

  inline
  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    value = that.value;
    location = that.location;
    return *this;
  }


  template <typename Base>
  inline
  void
  parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);

    // User destructor.
    YYUSE (yysym.type_get ());
  }

#if PLOGGRAMMAR_DEBUG
  template <typename Base>
  void
  parser::yy_print_ (std::ostream& yyo,
                                     const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    symbol_number_type yytype = yysym.type_get ();
    // Avoid a (spurious) G++ 4.8 warning about "array subscript is
    // below array bounds".
    if (yysym.empty ())
      std::abort ();
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " ("
        << yysym.location << ": ";
    YYUSE (yytype);
    yyo << ')';
  }
#endif

  inline
  void
  parser::yypush_ (const char* m, state_type s, symbol_type& sym)
  {
    stack_symbol_type t (s, sym);
    yypush_ (m, t);
  }

  inline
  void
  parser::yypush_ (const char* m, stack_symbol_type& s)
  {
    if (m)
      YY_SYMBOL_PRINT (m, s);
    yystack_.push (s);
  }

  inline
  void
  parser::yypop_ (unsigned int n)
  {
    yystack_.pop (n);
  }

#if PLOGGRAMMAR_DEBUG
  std::ostream&
  parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  parser::debug_level_type
  parser::debug_level () const
  {
    return yydebug_;
  }

  void
  parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // PLOGGRAMMAR_DEBUG

  inline parser::state_type
  parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  inline bool
  parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  inline bool
  parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  parser::parse ()
  {
    // State.
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

    // FIXME: This shoud be completely indented.  It is not yet to
    // avoid gratuitous conflicts when merging into the master branch.
    try
      {
    YYCDEBUG << "Starting parse" << std::endl;


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, yyla);

    // A new symbol was pushed on the stack.
  yynewstate:
    YYCDEBUG << "Entering state " << yystack_[0].state << std::endl;

    // Accept?
    if (yystack_[0].state == yyfinal_)
      goto yyacceptlab;

    goto yybackup;

    // Backup.
  yybackup:

    // Try to take a decision without lookahead.
    yyn = yypact_[yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token: ";
        try
          {
            yyla.type = yytranslate_ (yylex (&yyla.value, &yyla.location, lexer));
          }
        catch (const syntax_error& yyexc)
          {
            error (yyexc);
            goto yyerrlab1;
          }
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.type_get ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.type_get ())
      goto yydefault;

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", yyn, yyla);
    goto yynewstate;

  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;

  /*-----------------------------.
  | yyreduce -- Do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_(yystack_[yylen].state, yyr1_[yyn]);
      /* If YYLEN is nonzero, implement the default value of the
         action: '$$ = $1'.  Otherwise, use the top of the stack.

         Otherwise, the following line sets YYLHS.VALUE to garbage.
         This behavior is undocumented and Bison users should not rely
         upon it.  */
      if (yylen)
        yylhs.value = yystack_[yylen - 1].value;
      else
        yylhs.value = yystack_[0].value;

      // Compute the default @$.
      {
        slice<stack_symbol_type, stack_type> slice (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, slice, yylen);
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
      try
        {
          switch (yyn)
            {
  case 47:
#line 287 "ploggrammar.yy" // lalr1.cc:859
    {  }
#line 663 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 48:
#line 288 "ploggrammar.yy" // lalr1.cc:859
    {  }
#line 669 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 49:
#line 289 "ploggrammar.yy" // lalr1.cc:859
    {  }
#line 675 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 50:
#line 290 "ploggrammar.yy" // lalr1.cc:859
    {  }
#line 681 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 51:
#line 291 "ploggrammar.yy" // lalr1.cc:859
    {  }
#line 687 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 52:
#line 295 "ploggrammar.yy" // lalr1.cc:859
    {  }
#line 693 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 53:
#line 296 "ploggrammar.yy" // lalr1.cc:859
    {  }
#line 699 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 54:
#line 300 "ploggrammar.yy" // lalr1.cc:859
    {  }
#line 705 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 55:
#line 301 "ploggrammar.yy" // lalr1.cc:859
    {  }
#line 711 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 56:
#line 302 "ploggrammar.yy" // lalr1.cc:859
    { }
#line 717 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 57:
#line 303 "ploggrammar.yy" // lalr1.cc:859
    {  }
#line 723 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 62:
#line 317 "ploggrammar.yy" // lalr1.cc:859
    {}
#line 729 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 63:
#line 318 "ploggrammar.yy" // lalr1.cc:859
    {  }
#line 735 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 64:
#line 322 "ploggrammar.yy" // lalr1.cc:859
    {  }
#line 741 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 65:
#line 323 "ploggrammar.yy" // lalr1.cc:859
    {  }
#line 747 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 66:
#line 324 "ploggrammar.yy" // lalr1.cc:859
    {  }
#line 753 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 67:
#line 325 "ploggrammar.yy" // lalr1.cc:859
    {  }
#line 759 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 68:
#line 326 "ploggrammar.yy" // lalr1.cc:859
    {  }
#line 765 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 69:
#line 327 "ploggrammar.yy" // lalr1.cc:859
    {  }
#line 771 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 70:
#line 328 "ploggrammar.yy" // lalr1.cc:859
    {  }
#line 777 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 71:
#line 329 "ploggrammar.yy" // lalr1.cc:859
    {  }
#line 783 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 72:
#line 330 "ploggrammar.yy" // lalr1.cc:859
    {  }
#line 789 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 73:
#line 331 "ploggrammar.yy" // lalr1.cc:859
    {  }
#line 795 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 74:
#line 337 "ploggrammar.yy" // lalr1.cc:859
    {  }
#line 801 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 75:
#line 338 "ploggrammar.yy" // lalr1.cc:859
    {  }
#line 807 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 76:
#line 342 "ploggrammar.yy" // lalr1.cc:859
    {   }
#line 813 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 77:
#line 343 "ploggrammar.yy" // lalr1.cc:859
    {   }
#line 819 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 78:
#line 349 "ploggrammar.yy" // lalr1.cc:859
    {  }
#line 825 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 79:
#line 350 "ploggrammar.yy" // lalr1.cc:859
    {  }
#line 831 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 80:
#line 351 "ploggrammar.yy" // lalr1.cc:859
    {  }
#line 837 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 81:
#line 352 "ploggrammar.yy" // lalr1.cc:859
    {  }
#line 843 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 82:
#line 353 "ploggrammar.yy" // lalr1.cc:859
    {  }
#line 849 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 83:
#line 354 "ploggrammar.yy" // lalr1.cc:859
    {  }
#line 855 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 84:
#line 355 "ploggrammar.yy" // lalr1.cc:859
    {  }
#line 861 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 85:
#line 356 "ploggrammar.yy" // lalr1.cc:859
    {  }
#line 867 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 86:
#line 357 "ploggrammar.yy" // lalr1.cc:859
    {  }
#line 873 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 87:
#line 358 "ploggrammar.yy" // lalr1.cc:859
    {  }
#line 879 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 88:
#line 359 "ploggrammar.yy" // lalr1.cc:859
    {  }
#line 885 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 89:
#line 366 "ploggrammar.yy" // lalr1.cc:859
    {  }
#line 891 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 90:
#line 367 "ploggrammar.yy" // lalr1.cc:859
    {  }
#line 897 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 91:
#line 371 "ploggrammar.yy" // lalr1.cc:859
    {  }
#line 903 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 92:
#line 372 "ploggrammar.yy" // lalr1.cc:859
    {  }
#line 909 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 93:
#line 378 "ploggrammar.yy" // lalr1.cc:859
    {  }
#line 915 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 94:
#line 379 "ploggrammar.yy" // lalr1.cc:859
    {  }
#line 921 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 95:
#line 380 "ploggrammar.yy" // lalr1.cc:859
    {  }
#line 927 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 96:
#line 381 "ploggrammar.yy" // lalr1.cc:859
    {  }
#line 933 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 97:
#line 382 "ploggrammar.yy" // lalr1.cc:859
    {  }
#line 939 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 98:
#line 383 "ploggrammar.yy" // lalr1.cc:859
    {  }
#line 945 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 99:
#line 386 "ploggrammar.yy" // lalr1.cc:859
    {  }
#line 951 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 100:
#line 387 "ploggrammar.yy" // lalr1.cc:859
    {  }
#line 957 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 101:
#line 388 "ploggrammar.yy" // lalr1.cc:859
    { }
#line 963 "ploggrammar.tab.cc" // lalr1.cc:859
    break;


#line 967 "ploggrammar.tab.cc" // lalr1.cc:859
            default:
              break;
            }
        }
      catch (const syntax_error& yyexc)
        {
          error (yyexc);
          YYERROR;
        }
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;
      YY_STACK_PRINT ();

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, yylhs);
    }
    goto yynewstate;

  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        error (yyla.location, yysyntax_error_ (yystack_[0].state, yyla));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.type_get () == yyeof_)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:

    /* Pacify compilers like GCC when the user code never invokes
       YYERROR and the label yyerrorlab therefore never appears in user
       code.  */
    if (false)
      goto yyerrorlab;
    yyerror_range[1].location = yystack_[yylen - 1].location;
    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    goto yyerrlab1;

  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    {
      stack_symbol_type error_token;
      for (;;)
        {
          yyn = yypact_[yystack_[0].state];
          if (!yy_pact_value_is_default_ (yyn))
            {
              yyn += yyterror_;
              if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yyterror_)
                {
                  yyn = yytable_[yyn];
                  if (0 < yyn)
                    break;
                }
            }

          // Pop the current state because it cannot handle the error token.
          if (yystack_.size () == 1)
            YYABORT;

          yyerror_range[1].location = yystack_[0].location;
          yy_destroy_ ("Error: popping", yystack_[0]);
          yypop_ ();
          YY_STACK_PRINT ();
        }

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = yyn;
      yypush_ ("Shifting", error_token);
    }
    goto yynewstate;

    // Accept.
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;

    // Abort.
  yyabortlab:
    yyresult = 1;
    goto yyreturn;

  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack"
                 << std::endl;
        // Do not try to display the values of the reclaimed symbols,
        // as their printer might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
  }

  void
  parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what());
  }

  // Generate an error message.
  std::string
  parser::yysyntax_error_ (state_type yystate, const symbol_type& yyla) const
  {
    // Number of reported tokens (one for the "unexpected", one per
    // "expected").
    size_t yycount = 0;
    // Its maximum.
    enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
    // Arguments of yyformat.
    char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];

    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state
         merging (from LALR or IELR) and default reductions corrupt the
         expected token list.  However, the list is correct for
         canonical LR with one exception: it will still contain any
         token that will not be accepted due to an error action in a
         later state.
    */
    if (!yyla.empty ())
      {
        int yytoken = yyla.type_get ();
        yyarg[yycount++] = yytname_[yytoken];
        int yyn = yypact_[yystate];
        if (!yy_pact_value_is_default_ (yyn))
          {
            /* Start YYX at -YYN if negative to avoid negative indexes in
               YYCHECK.  In other words, skip the first -YYN actions for
               this state because they are default actions.  */
            int yyxbegin = yyn < 0 ? -yyn : 0;
            // Stay within bounds of both yycheck and yytname.
            int yychecklim = yylast_ - yyn + 1;
            int yyxend = yychecklim < yyntokens_ ? yychecklim : yyntokens_;
            for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
              if (yycheck_[yyx + yyn] == yyx && yyx != yyterror_
                  && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
                {
                  if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                    {
                      yycount = 1;
                      break;
                    }
                  else
                    yyarg[yycount++] = yytname_[yyx];
                }
          }
      }

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
        YYCASE_(0, YY_("syntax error"));
        YYCASE_(1, YY_("syntax error, unexpected %s"));
        YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    size_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += yytnamerr_ (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const signed char parser::yypact_ninf_ = -87;

  const signed char parser::yytable_ninf_ = -101;

  const short int
  parser::yypact_[] =
  {
     107,   119,    13,   -87,   -87,   -87,   -28,   -87,   -87,    68,
      40,   136,    46,   125,    40,   -87,    49,   151,   -87,   153,
     -87,   156,    49,   140,   135,   -87,   130,   155,   164,   164,
     -87,   142,   165,    45,   -87,    -7,   141,   163,   166,    86,
     -87,    85,   -87,   -87,   143,   143,   -87,   134,   -87,   110,
     175,   -87,   156,   130,   130,   170,     2,   -87,   174,   -87,
     -87,   -87,    64,   186,   121,   -87,    76,   -87,   156,   -87,
     164,   164,   164,   164,   164,   164,   -87,   135,    36,   -87,
     -87,   167,   168,   141,   143,   143,   -87,    74,   179,   192,
     -87,   143,   -87,   -87,   -87,   -87,   -87,   143,   -87,   143,
     143,   143,   143,   143,   -87,   -87,   196,   180,    12,    43,
     130,   130,   -87,   130,   130,   -87,   164,   -87,   197,   199,
     -87,   181,   162,   189,   189,   189,   189,   162,   -87,    81,
     -87,   216,   145,   204,   194,   194,   222,   202,   -87,   116,
     143,   -87,   203,   209,   209,   209,   209,   206,   194,   156,
     -87,   -87,   -87,     0,     8,   -87,   201,   -87,   201,    45,
     -87,   220,   -87,   -87,   200,   221,   205,    81,   143,   234,
     -87,   210,    72,   -87,   207,   130,   237,   -87,   208,   -87,
     211,   213,    41,   194,   143,   -87,   215,   -87,   -13,   212,
     241,   -87,   245,   194,   -87,   -13,   190,   122,   -87,   214,
     200,     5,   217,   -13,   -13,   232,   -87,   -87,   -87,   -87,
     250,   218,   223,   230,   227,   -87
  };

  const unsigned char
  parser::yydefact_[] =
  {
       6,     0,     0,     1,    11,    39,     0,     5,     7,     0,
       0,     9,    37,     0,     0,    46,     0,     0,    10,     0,
      38,     0,     0,    44,     0,     3,     0,     0,     0,     0,
      73,    72,     0,    62,     2,     0,     0,     0,     0,    54,
      45,     0,    52,    53,     0,     0,    87,    86,    88,     0,
       0,    16,    77,     0,     0,    72,     0,    13,    14,    24,
      15,    17,     0,    42,     0,    72,     0,    70,    77,     8,
       0,     0,     0,     0,     0,     0,    51,     0,     0,   102,
      61,     0,     0,     0,     0,    92,    47,     0,    86,     0,
      83,    92,    97,    95,    93,    96,    94,     0,    98,     0,
       0,     0,     0,     0,   107,    74,    76,     0,     0,     0,
       0,     0,    12,     0,     0,    23,     0,    41,     0,     0,
      71,     0,    64,    66,    68,    69,    67,    65,   103,     0,
      50,     0,     0,     0,    57,    89,    91,     0,    48,     0,
      92,    85,     0,    79,    81,    82,    80,    78,   101,     0,
      36,    25,    21,    34,     0,    33,    18,    19,    20,    22,
      43,     0,    63,    60,     0,     0,     0,     0,     0,    55,
      49,     0,    84,    75,     0,     0,    26,    40,     0,   105,
       0,     0,     0,    90,     0,    84,     0,    32,     0,     0,
       0,    58,     0,    56,    35,     0,     0,    27,   106,     0,
       0,     0,     0,     0,     0,     0,   104,    31,    28,    30,
      29,     0,     0,     0,     0,    59
  };

  const short int
  parser::yypgoto_[] =
  {
     -87,   -87,   -87,   -87,   -87,   -87,   -87,   -87,   -23,   -87,
     -87,   219,   -87,   -43,   -87,    87,   -87,   254,   -87,   -87,
     -87,   251,   -87,   -87,   -87,   -14,   -87,   -83,   -19,    -8,
     -87,   198,   -44,   -87,   -86,    71,   -16,   139,    69,   242
  };

  const short int
  parser::yydefgoto_[] =
  {
      -1,     1,     2,     7,     8,     9,    11,    18,   153,    57,
      58,    59,    60,   197,   154,   155,    61,    10,    12,    20,
      64,    16,    23,    40,    41,    42,    43,    78,   105,    62,
     106,   107,    49,   136,   137,   103,    79,    80,   179,    25
  };

  const short int
  parser::yytable_[] =
  {
      89,    90,    32,    56,   139,   142,    76,   111,    50,   111,
     195,   203,    13,    33,    44,   112,     4,     5,   175,   111,
      66,    67,    81,   174,     6,   113,   204,   113,   196,    45,
     108,   109,    46,    47,    48,    77,   114,   113,   114,   207,
     134,   135,   176,   151,    33,    15,   129,   135,   114,   130,
     111,   129,    70,   143,   171,   144,   145,   146,   147,   148,
      33,   128,   122,   123,   124,   125,   126,   127,   113,   133,
      71,    70,     5,    72,    73,   192,    24,   152,   116,   114,
      74,    75,  -100,    70,   182,  -100,    19,   138,   156,    71,
     157,   158,    72,    73,    84,    44,   135,   120,    86,    74,
      75,    71,    44,    87,    72,    73,  -100,    -4,   159,    85,
      45,    74,    75,    46,    47,    48,    77,    45,    92,     3,
      46,    47,    48,    77,   183,    93,   129,    94,   203,   170,
     173,   118,    95,    21,    96,    97,    98,   119,    99,   100,
     193,    33,    51,   204,   -99,   101,   102,   -99,    17,    52,
      53,    28,   201,    54,   165,   166,    44,    91,    35,    26,
     209,   210,    27,    36,    44,    68,    29,    63,   -99,    30,
      55,    45,    37,    38,    46,    47,    48,    28,    69,    45,
      39,    39,    46,    88,    48,    28,    82,    71,   104,    83,
      72,    73,    29,   110,    53,    30,    31,    74,    92,   117,
      29,   131,   140,    30,    65,    93,   149,    94,   132,   160,
     150,   161,    95,   141,    96,   162,    98,    97,    73,    97,
      99,   100,    99,   100,   164,   167,   113,   101,   102,   101,
     102,    97,   168,   177,    99,   100,   169,   172,   100,   178,
     180,   101,   184,   189,   185,   181,   188,   191,   186,   194,
     199,   198,   190,   200,   205,   211,   203,   213,   208,   212,
     214,   215,   187,    14,    34,    22,   121,   202,   163,   206,
       0,     0,     0,     0,     0,     0,     0,   115
  };

  const short int
  parser::yycheck_[] =
  {
      44,    45,    21,    26,    87,    91,    13,     7,    24,     7,
      23,     6,    40,    21,    21,    13,     3,     4,    10,     7,
      28,    29,    36,    23,    11,    25,    21,    25,    41,    36,
      53,    54,    39,    40,    41,    42,    36,    25,    36,    34,
      84,    85,    34,    31,    52,     5,    10,    91,    36,    13,
       7,    10,     7,    97,   140,    99,   100,   101,   102,   103,
      68,    77,    70,    71,    72,    73,    74,    75,    25,    83,
      25,     7,     4,    28,    29,    34,    27,    34,    14,    36,
      35,    36,    10,     7,   167,    13,    40,    13,   111,    25,
     113,   114,    28,    29,     8,    21,   140,    21,    13,    35,
      36,    25,    21,    18,    28,    29,    34,     0,   116,    23,
      36,    35,    36,    39,    40,    41,    42,    36,     8,     0,
      39,    40,    41,    42,   168,    15,    10,    17,     6,    13,
     149,    10,    22,     8,    24,    25,    26,    16,    28,    29,
     184,   149,    12,    21,    10,    35,    36,    13,    12,    19,
      20,    21,   195,    23,     9,    10,    21,    23,    18,     8,
     203,   204,     9,    23,    21,    23,    36,    12,    34,    39,
      40,    36,    32,    33,    39,    40,    41,    21,    13,    36,
      40,    40,    39,    40,    41,    21,    23,    25,    13,    23,
      28,    29,    36,    23,    20,    39,    40,    35,     8,    13,
      36,    34,    23,    39,    40,    15,    10,    17,    40,    12,
      30,    12,    22,    21,    24,    34,    26,    25,    29,    25,
      28,    29,    28,    29,     8,    21,    25,    35,    36,    35,
      36,    25,    10,    13,    28,    29,    34,    34,    29,    39,
      19,    35,     8,    35,    34,    40,     9,    34,    41,    34,
       9,    39,    41,     8,    40,    23,     6,    34,    41,    41,
      30,    34,   175,     9,    22,    14,    68,   196,   129,   200,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    58
  };

  const unsigned char
  parser::yystos_[] =
  {
       0,    44,    45,     0,     3,     4,    11,    46,    47,    48,
      60,    49,    61,    40,    60,     5,    64,    12,    50,    40,
      62,     8,    64,    65,    27,    82,     8,     9,    21,    36,
      39,    40,    71,    72,    82,    18,    23,    32,    33,    40,
      66,    67,    68,    69,    21,    36,    39,    40,    41,    75,
      79,    12,    19,    20,    23,    40,    51,    52,    53,    54,
      55,    59,    72,    12,    63,    40,    72,    72,    23,    13,
       7,    25,    28,    29,    35,    36,    13,    42,    70,    79,
      80,    68,    23,    23,     8,    23,    13,    18,    40,    75,
      75,    23,     8,    15,    17,    22,    24,    25,    26,    28,
      29,    35,    36,    78,    13,    71,    73,    74,    51,    51,
      23,     7,    13,    25,    36,    54,    14,    13,    10,    16,
      21,    74,    72,    72,    72,    72,    72,    72,    79,    10,
      13,    34,    40,    68,    75,    75,    76,    77,    13,    70,
      23,    21,    77,    75,    75,    75,    75,    75,    75,    10,
      30,    31,    34,    51,    57,    58,    51,    51,    51,    72,
      12,    12,    34,    80,     8,     9,    10,    21,    10,    34,
      13,    77,    34,    71,    23,    10,    34,    13,    39,    81,
      19,    40,    70,    75,     8,    34,    41,    58,     9,    35,
      41,    34,    34,    75,    34,    23,    41,    56,    39,     9,
       8,    56,    78,     6,    21,    40,    81,    34,    41,    56,
      56,    23,    41,    34,    30,    34
  };

  const unsigned char
  parser::yyr1_[] =
  {
       0,    43,    44,    44,    44,    45,    45,    46,    47,    48,
      49,    49,    50,    51,    51,    51,    51,    51,    51,    51,
      51,    51,    52,    53,    53,    54,    55,    55,    56,    56,
      56,    56,    57,    57,    58,    58,    59,    60,    61,    61,
      62,    62,    63,    63,    64,    65,    65,    66,    66,    66,
      66,    66,    67,    67,    68,    68,    68,    68,    69,    69,
      70,    70,    71,    71,    72,    72,    72,    72,    72,    72,
      72,    72,    72,    72,    73,    73,    74,    74,    75,    75,
      75,    75,    75,    75,    75,    75,    75,    75,    75,    76,
      76,    77,    77,    78,    78,    78,    78,    78,    78,    79,
      79,    79,    80,    80,    66,    66,    81,    82
  };

  const unsigned char
  parser::yyr2_[] =
  {
       0,     2,     5,     4,     0,     2,     0,     1,     5,     2,
       2,     0,     4,     1,     1,     1,     1,     1,     3,     3,
       3,     3,     3,     2,     1,     3,     4,     6,     3,     3,
       3,     3,     3,     1,     1,     4,     3,     2,     2,     0,
       6,     4,     1,     3,     2,     2,     0,     2,     3,     4,
       3,     2,     1,     1,     1,     4,     6,     3,     6,    13,
       3,     1,     1,     4,     3,     3,     3,     3,     3,     3,
       2,     3,     1,     1,     1,     3,     1,     0,     3,     3,
       3,     3,     3,     2,     4,     3,     1,     1,     1,     1,
       3,     1,     0,     1,     1,     1,     1,     1,     1,     1,
       4,     3,     1,     2,     8,     5,     3,     3
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const parser::yytname_[] =
  {
  "\"<EOF>\"", "error", "$undefined", "SORTDEFKEYWORD", "ATTDEFKEYWORD",
  "STMTDEFKEYWORD", "\"&\"", "\"+\"", "\"=\"", "\":\"", "\",\"",
  "\"#const\"", "SORT_NAME", "\".\"", "\"..\"", "\">=\"", "\"->\"",
  "\">\"", "\":-\"", "\"{\"", "\"[\"", "\"|\"", "\"<=\"", "\"(\"", "\"<\"",
  "\"*\"", "\"!=\"", "\"?\"", "\"\\\\\"", "\"^\"", "\"}\"", "\"]\"",
  "\"random\"", "\"pr\"", "\")\"", "\"/\"", "\"-\"", "UBNOT", "UMINUS",
  "\"<NUMBER>\"", "\"<IDENTIFIER>\"", "\"<VARIABLE>\"", "\"not\"",
  "$accept", "program", "directives", "directive", "const_decl",
  "sorts_sec", "sort_defs", "sort_def", "sort_expr", "range",
  "concatenation", "concat_elem", "functional_symbol", "cond",
  "sort_expr_list", "var_sort_expr", "curly_brackets", "atts_sec",
  "att_defs", "att_def", "sort_name_list", "stmts_sec", "stmts", "stmt",
  "head", "head_atom", "random_atom", "body", "constterm",
  "comparable_constterm", "consttermvec", "constargvec", "term",
  "ntermvec", "termvec", "cmp", "literal", "e_literal", "probability",
  "query", YY_NULLPTR
  };

#if PLOGGRAMMAR_DEBUG
  const unsigned short int
  parser::yyrline_[] =
  {
       0,   170,   170,   171,   171,   181,   182,   185,   189,   198,
     201,   202,   205,   209,   210,   211,   212,   213,   214,   215,
     216,   217,   220,   223,   224,   227,   230,   231,   234,   235,
     236,   237,   243,   244,   247,   248,   251,   258,   260,   261,
     264,   265,   268,   269,   276,   279,   280,   287,   288,   289,
     290,   291,   295,   296,   300,   301,   302,   303,   306,   307,
     311,   312,   317,   318,   322,   323,   324,   325,   326,   327,
     328,   329,   330,   331,   337,   338,   342,   343,   349,   350,
     351,   352,   353,   354,   355,   356,   357,   358,   359,   366,
     367,   371,   372,   378,   379,   380,   381,   382,   383,   386,
     387,   388,   391,   392,   396,   397,   400,   403
  };

  // Print the state stack on the debug stream.
  void
  parser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << i->state;
    *yycdebug_ << std::endl;
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  parser::yy_reduce_print_ (int yyrule)
  {
    unsigned int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):" << std::endl;
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // PLOGGRAMMAR_DEBUG

  // Symbol number corresponding to token number t.
  inline
  parser::token_number_type
  parser::yytranslate_ (int t)
  {
    static
    const token_number_type
    translate_table[] =
    {
     0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42
    };
    const unsigned int user_token_number_max_ = 297;
    const token_number_type undef_token_ = 2;

    if (static_cast<int>(t) <= yyeof_)
      return yyeof_;
    else if (static_cast<unsigned int> (t) <= user_token_number_max_)
      return translate_table[t];
    else
      return undef_token_;
  }

#line 19 "ploggrammar.yy" // lalr1.cc:1167
} // PlogGrammar
#line 1547 "ploggrammar.tab.cc" // lalr1.cc:1167
