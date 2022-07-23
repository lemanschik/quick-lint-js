// Copyright (C) 2020  Matthew "strager" Glazar
// See end of file for extended copyright information.

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <quick-lint-js/cli/cli-location.h>
#include <quick-lint-js/container/padded-string.h>
#include <quick-lint-js/diag-collector.h>
#include <quick-lint-js/diag-matcher.h>
#include <quick-lint-js/fe/diagnostic-types.h>
#include <quick-lint-js/fe/parse.h>
#include <quick-lint-js/fe/token.h>
#include <quick-lint-js/parse-support.h>
#include <quick-lint-js/port/char8.h>
#include <quick-lint-js/port/unreachable.h>
#include <quick-lint-js/port/warning.h>
#include <quick-lint-js/util/narrow-cast.h>
#include <string>
#include <string_view>

using ::testing::ElementsAre;
using ::testing::IsEmpty;
using namespace std::literals::string_literals;

namespace quick_lint_js {
namespace {
class test_parse_expression_typescript : public test_parse_expression {
 public:
  using test_parse_expression::make_parser;
  using test_parse_expression::parse_expression;

  test_parser& make_parser(string8_view input) {
    return this->make_parser(input, typescript_options);
  }

  expression* parse_expression(string8_view input) {
    return this->parse_expression(input, typescript_options);
  }
};

TEST_F(test_parse_expression_typescript, type_annotation) {
  // These would normally appear in arrow function parameter lists.

  {
    test_parser& p = this->make_parser(u8"x: Type"_sv);
    expression* ast = p.parse_expression();
    ASSERT_EQ(ast->kind(), expression_kind::type_annotated);
    EXPECT_EQ(summarize(ast->child_0()), "var x");
    EXPECT_THAT(p.errors(), IsEmpty());
    EXPECT_EQ(p.range(ast).begin_offset(), 0);
    EXPECT_EQ(p.range(ast).end_offset(), strlen(u8"x: Type"));

    spy_visitor v;
    static_cast<expression::type_annotated*>(ast)->visit_type_annotation(v);
    EXPECT_THAT(v.visits, ElementsAre("visit_variable_type_use"));
    EXPECT_THAT(v.variable_uses, ElementsAre(u8"Type"));
  }

  {
    expression* ast = this->parse_expression(u8"{x}: Type"_sv);
    EXPECT_EQ(ast->kind(), expression_kind::type_annotated);
    EXPECT_EQ(summarize(ast->child_0()), "object(literal: var x)");
  }

  {
    expression* ast = this->parse_expression(u8"[x]: Type"_sv);
    EXPECT_EQ(ast->kind(), expression_kind::type_annotated);
    EXPECT_EQ(summarize(ast->child_0()), "array(var x)");
  }
}

TEST_F(test_parse_expression_typescript,
       conditional_colon_is_not_a_type_annotation) {
  {
    expression* ast = this->parse_expression(u8"cond ? x: Type"_sv);
    EXPECT_EQ(summarize(ast), "cond(var cond, var x, var Type)");
  }
}

TEST_F(test_parse_expression_typescript, non_null_assertion) {
  {
    expression* ast = this->parse_expression(u8"x!"_sv);
    EXPECT_EQ(summarize(ast), "nonnull(var x)");
  }

  {
    expression* ast = this->parse_expression(u8"f()!.someprop"_sv);
    EXPECT_EQ(summarize(ast), "dot(nonnull(call(var f)), someprop)");
  }

  {
    expression* ast = this->parse_expression(u8"x! = y"_sv);
    EXPECT_EQ(summarize(ast), "assign(nonnull(var x), var y)");
  }

  {
    expression* ast = this->parse_expression(u8"async!"_sv);
    EXPECT_EQ(summarize(ast), "nonnull(var async)");
  }
}

TEST_F(test_parse_expression_typescript,
       non_null_assertion_does_not_allow_newline) {
  {
    // HACK(strager): We rely on the fact that parse_expression stops parsing at
    // the end of the line. "!+y" part is unparsed.
    expression* ast = this->parse_expression(u8"x\n!+y"_sv);
    EXPECT_EQ(summarize(ast), "var x");
  }
}

TEST_F(test_parse_expression_typescript,
       non_null_assertion_not_allowed_in_javascript) {
  test_parser p(u8"x!"_sv, javascript_options);
  expression* ast = p.parse_expression();
  EXPECT_EQ(summarize(ast), "nonnull(var x)");
  EXPECT_THAT(
      p.errors(),
      ElementsAre(DIAG_TYPE_OFFSETS(
          p.code(),
          diag_typescript_non_null_assertion_not_allowed_in_javascript,  //
          bang, strlen(u8"x"), u8"!")));
}

TEST(test_parse_expression_typescript_statement, non_null_assertion) {
  {
    parse_visit_collector v =
        parse_and_visit_typescript_statement(u8"f(x!);"_sv);
    EXPECT_THAT(v.visits, ElementsAre("visit_variable_use",    // f
                                      "visit_variable_use"));  // x
    EXPECT_THAT(v.variable_uses, ElementsAre(u8"f", u8"x"));
  }

  {
    parse_visit_collector v =
        parse_and_visit_typescript_statement(u8"x! = null;"_sv);
    EXPECT_THAT(v.visits, ElementsAre("visit_variable_assignment"));  // x
  }
}
}
}

// quick-lint-js finds bugs in JavaScript programs.
// Copyright (C) 2020  Matthew "strager" Glazar
//
// This file is part of quick-lint-js.
//
// quick-lint-js is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// quick-lint-js is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with quick-lint-js.  If not, see <https://www.gnu.org/licenses/>.
