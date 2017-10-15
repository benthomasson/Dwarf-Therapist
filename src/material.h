/*
Dwarf Therapist
Copyright (c) 2009 Trey Stout (chmod)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/
#ifndef MATERIAL_H
#define MATERIAL_H

#include <QObject>
#include "utils.h"
#include "global_enums.h"
#include "flagarray.h"

class DFInstance;
class MemoryLayout;

class Material : public QObject {
    Q_OBJECT
public:
    Material(QObject *parent = 0);
    Material(DFInstance *df, VIRTADDR address, int index, bool inorganic = false, QObject *parent = 0);
    virtual ~Material();

    static Material* get_material(DFInstance *df, const VIRTADDR &address, int index, bool inorganic = false, QObject *parent = 0);

    //! Return the memory address (in hex) of this Material in the remote DF process
    VIRTADDR address() {return m_address;}

    QString get_material_name(MATERIAL_STATES state);
    int id() {return m_index;}

    void load_data();
    bool is_inorganic() {return m_inorganic;}
    bool is_generated() {return m_is_generated;}

    FlagArray flags() {return m_flags;}

    static QString get_material_flag_desc(MATERIAL_FLAGS flag, MATERIAL_STATES state = SOLID) {
        switch (flag) {
        case BONE: return tr("Bone");
        case TOOTH: return tr("Ivory/Tooth");
        case HORN: return tr("Horn/Hoof");
        case PEARL: return tr("Pearl");
        case SHELL: return tr("Shell");
        case LEATHER: return tr("Leather");
        case SILK: return tr("Silk");
        case IS_GEM: return tr("Gems");
        case IS_GLASS: return tr("Glass");
        case IS_WOOD: return tr("Wood");
        case IS_STONE: return tr("Stone");
        case IS_METAL: return tr("Metal");
        case THREAD_PLANT: return (state == PRESSED ? tr("Paper") : tr("Cloth"));
        case YARN: return tr("Yarn/Wool/Fur");
        default: return tr("Missing Description");
        }
    }

private:
    int m_index;
    VIRTADDR m_address;
    VIRTADDR m_flag_address;
    DFInstance * m_df;
    MemoryLayout * m_mem;
    FlagArray m_flags;
    bool m_inorganic;
    bool m_is_generated;
    QHash<MATERIAL_STATES, QString> m_state_names;
    QString m_prefix;

    void read_material();
};

#endif // MATERIAL_H
