---
title: "Extract Point Cloud from Blender mesh"
last_modified_at: 2019-04-15T20:52:14+09:00
categories:
    - 3D
tags:
    - [Python, Blender]
---

I had a chance to make a sample point cloud which is mathematically generated and perfectly designed to compare alignment performance. I thought it's quite obvious to get point cloud but wasn't on blender. Here's the python script how to export .ply file from Blender mesh.

[Reference : How can I create a point cloud from the surfaces of a model?](https://blender.stackexchange.com/questions/19655/how-can-i-create-a-point-cloud-from-the-surfaces-of-a-model)

I referenced this article and modified the code to make point on triangle's edges, not on middle of triangles.

```python
import bpy
import bmesh

# ---------------------------------------------------------------------
# create vertices
# ---------------------------------------------------------------------
# verts: list of position coords - [(-1.0, 1.0, 0.0), (-1.0, -1.0, 0.0)]
# returns the new object

def create_Vertices (name, verts):
    me = bpy.data.meshes.new(name+'Mesh')
    ob = bpy.data.objects.new(name, me)
    ob.show_name = True
    bpy.context.scene.objects.link(ob)
    me.from_pydata(verts, [], [])
    me.update()
    return ob

# -----------------------------------------------------------------------
# get face positions from a mesh object
# -----------------------------------------------------------------------
# returns: absolute face center positions

def face_Positions_From_Object(meshObj):
    me = meshObj.data
    bm = bmesh.new()
    bm.from_mesh(me)
    bmFaces = set()


    for face in bm.faces:
        v = meshObj.matrix_world * face.verts[0].co
        v.freeze()
        bmFaces.add(v)
        v = meshObj.matrix_world * face.verts[1].co
        v.freeze()
        bmFaces.add(v)
        v = meshObj.matrix_world * face.verts[2].co
        v.freeze()
        bmFaces.add(v)

    return bmFaces

# -----------------------------------------------------------------------
# do it
# -----------------------------------------------------------------------

obj = bpy.context.active_object
facePosOfObj = face_Positions_From_Object(obj)
pointCloud = create_Vertices(obj.name + '_pointcloud', facePosOfObj)
```

<br/>
On this section,

```python
v = meshObj.matrix_world * face.verts[0].co
v.freeze()
bmFaces.add(v)
```

It will multiply mesh's world coordinate and triangle's 1st edge's coordinate.

Then call freeze() to make vector immutable. [mathutils.Vector.freeze](https://docs.blender.org/api/blender2.8/mathutils.html?highlight=freeze#mathutils.Vector.freeze)

And put it into Set. Then there won't be duplicated verticies and only all of edges coordinates.


Happy 3D hacking :)
