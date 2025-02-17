/*
 * Copyright (C) 1999 Lars Knoll (knoll@kde.org)
 *           (C) 1999 Antti Koivisto (koivisto@kde.org)
 * Copyright (C) 2004, 2005, 2006, 2007, 2010 Apple Inc. All rights reserved.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#include "core/html/HTMLMapElement.h"

#include "core/HTMLNames.h"
#include "core/dom/Document.h"
#include "core/dom/ElementTraversal.h"
#include "core/dom/NodeListsNodeData.h"
#include "core/frame/UseCounter.h"
#include "core/html/HTMLAreaElement.h"
#include "core/html/HTMLCollection.h"
#include "core/html/HTMLImageElement.h"
#include "core/layout/HitTestResult.h"

namespace blink {

using namespace HTMLNames;

inline HTMLMapElement::HTMLMapElement(Document& document)
    : HTMLElement(mapTag, document) {
  UseCounter::Count(document, WebFeature::kMapElement);
}

DEFINE_NODE_FACTORY(HTMLMapElement)

HTMLMapElement::~HTMLMapElement() {}

HTMLAreaElement* HTMLMapElement::AreaForPoint(
    const LayoutPoint& location,
    const LayoutObject* container_object) {
  HTMLAreaElement* default_area = nullptr;
  for (HTMLAreaElement& area :
       Traversal<HTMLAreaElement>::DescendantsOf(*this)) {
    if (area.IsDefault() && !default_area)
      default_area = &area;
    else if (area.PointInArea(location, container_object))
      return &area;
  }

  return default_area;
}

HTMLImageElement* HTMLMapElement::ImageElement() {
  HTMLCollection* images = GetDocument().images();
  for (unsigned i = 0; Element* curr = images->item(i); ++i) {
    // The HTMLImageElement's useMap() value includes the '#' symbol at the
    // beginning, which has to be stripped off.
    HTMLImageElement& image_element = toHTMLImageElement(*curr);
    String use_map_name =
        image_element.getAttribute(usemapAttr).GetString().Substring(1);
    if (use_map_name == name_)
      return &image_element;
  }

  return nullptr;
}

void HTMLMapElement::ParseAttribute(const AttributeModificationParams& params) {
  // FIXME: This logic seems wrong for XML documents.
  // Either the id or name will be used depending on the order the attributes
  // are parsed.

  if (params.name == idAttr || params.name == nameAttr) {
    if (params.name == idAttr) {
      // Call base class so that hasID bit gets set.
      HTMLElement::ParseAttribute(params);
      if (GetDocument().IsHTMLDocument())
        return;
    }
    if (isConnected())
      GetTreeScope().RemoveImageMap(this);
    String map_name = params.new_value;
    if (map_name[0] == '#')
      map_name = map_name.Substring(1);
    name_ = AtomicString(map_name);
    if (isConnected())
      GetTreeScope().AddImageMap(this);

    return;
  }

  HTMLElement::ParseAttribute(params);
}

HTMLCollection* HTMLMapElement::areas() {
  return EnsureCachedCollection<HTMLCollection>(kMapAreas);
}

Node::InsertionNotificationRequest HTMLMapElement::InsertedInto(
    ContainerNode* insertion_point) {
  if (insertion_point->isConnected())
    GetTreeScope().AddImageMap(this);
  return HTMLElement::InsertedInto(insertion_point);
}

void HTMLMapElement::RemovedFrom(ContainerNode* insertion_point) {
  if (insertion_point->isConnected())
    GetTreeScope().RemoveImageMap(this);
  HTMLElement::RemovedFrom(insertion_point);
}

}  // namespace blink
