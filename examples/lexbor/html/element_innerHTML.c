/*
 * Copyright (C) 2018 Alexander Borisov
 *
 * Author: Alexander Borisov <lex.borisov@gmail.com>
 */

#include "examples/lexbor/html/base.h"

#include <lexbor/html/interfaces/element.h>


int
main(int argc, const char *argv[])
{
    lxb_html_element_t *element;
    lxb_html_body_element_t *body;
    lxb_html_document_t *document;

    static const lxb_char_t html[] = "<div><span>blah-blah-blah</div>";
    size_t html_len = sizeof(html) - 1;

    static const lxb_char_t inner[] = "<ul><li>1<li>2<li>3</ul>";
    size_t inner_len = sizeof(inner) - 1;

    /* Parse */
    document = parse(html, html_len);
    if (document == NULL) {
        FAILED("Failed to create Document object");
    }

    /* Print Incoming Data */
    PRINT("HTML:");
    PRINT("%s", (const char *) html);
    PRINT("\nTree after parse:");
    serialize(lxb_dom_interface_node(document));

    /* Get BODY elemenet */
    body = lxb_html_document_body_element(document);

    PRINT("\nHTML for innerHTML:");
    PRINT("%s", (const char *) inner);

    element = lxb_html_element_inner_html_set(lxb_html_interface_element(body),
                                              inner, inner_len);
    if (element == NULL) {
        FAILED("Failed to parse innerHTML");
    }

    /* Print Result */
    PRINT("\nTree after innerHTML set:");
    serialize(lxb_dom_interface_node(document));

    /* Destroy all */
    lxb_html_document_destroy(document);

    return 0;
}
