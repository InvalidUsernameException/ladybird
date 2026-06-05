/*
 * Copyright (c) 2026, Ladybird contributors
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include "ContrastColorStyleValue.h"

namespace Web::CSS {

bool ContrastColorStyleValue::equals(StyleValue const& other) const
{
    auto const* other_contrast_color = as_if<ContrastColorStyleValue>(other);
    if (!other_contrast_color)
        return false;
    return m_inner_color == other_contrast_color->m_inner_color;
}

Optional<Color> ContrastColorStyleValue::to_color(ColorResolutionContext color_resolution_context) const
{
    auto inner_color = m_inner_color->to_color(color_resolution_context);
    if (!inner_color.has_value())
        return {};
    return inner_color.value().contrast_color();
}

ValueComparingNonnullRefPtr<StyleValue const> ContrastColorStyleValue::absolutized(ComputationContext const& context) const
{
    return ContrastColorStyleValue::create(m_inner_color->absolutized(context));
}

void ContrastColorStyleValue::serialize(StringBuilder& builder, SerializationMode mode) const
{
    builder.append("contrast-color("sv);
    m_inner_color->serialize(builder, mode);
    builder.append(')');
}

}
