/**
 * simcom helpers
 *
 * Copyright (C) 2022, Manel J
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once
#include <memory>

#ifdef _WIN32
#ifdef SIMCOM_EXPORTS
#define SIMCOM_API __declspec(dllexport)
#else
#define SIMCOM_API __declspec(dllimport)
#endif
#else
#define SIMCOM_API
#endif

#if __cplusplus >= 201703L
#define NODISCARD [[nodiscard]] /*NOLINT*/
#else
#define NODISCARD /*NOLINT*/
#endif

#define DISABLE_COPY(class_name) /*NOLINT*/                                                                            \
    class_name(const class_name& other) = delete;                                                                      \
    class_name& operator=(class_name& other) = delete; /*NOLINT*/

#define DISABLE_MOVE(class_name) /*NOLINT*/                                                                            \
    class_name(const class_name&& other) = delete;                                                                     \
    class_name& operator=(class_name&& other) = delete; /*NOLINT*/

#define DISABLE_COPY_AND_MOVE(class_name) /*NOLINT*/                                                                   \
    DISABLE_COPY(class_name)                                                                                           \
    DISABLE_MOVE(class_name)

// NOLINTNEXTLINE
#define PIMPL(implClass)                                                                                               \
    const implClass* Pimpl() const                                                                                     \
    {                                                                                                                  \
        return m_pImpl.get();                                                                                          \
    }                                                                                                                  \
    implClass* Pimpl() /*NOLINT*/                                                                                      \
    {                                                                                                                  \
        return m_pImpl.get();                                                                                          \
    }                                                                                                                  \
    std::unique_ptr<implClass> m_pImpl;
