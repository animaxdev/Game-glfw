//
//  Created by Cod3r Kane on 10/22/2016
//

#ifndef GAME_RAWMODEL_H
#define GAME_RAWMODEL_H

class RawModel {
private:
    int VaoID;
    int VertexCount;
public:

    /**
     * Normal constructor class
     * @param int VaoID
     * @param int VertexCount
     */
    RawModel(int VaoID, int VertexCount);

    /**
     * Empty constructor class
     */
    RawModel() {};

    /**
     * Get VaoID
     * @return int
     */
    int getVaoID() const;

    /**
     * set VaoID
     * @param int VaoID
     */
    void setVaoID(int VaoID);

    /**
     * get VertexCount
     * @return int
     */
    int getVertexCount() const;

    /**
     * set VertexCount
     * @param int VertexCount
     */
    void setVertexCount(int VertexCount);
};

#endif // GAME_OBJLOADER_H