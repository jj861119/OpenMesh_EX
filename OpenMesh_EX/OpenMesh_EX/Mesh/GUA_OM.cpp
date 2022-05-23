#include"TextureApp.h"
#include "GUA_OM.h"
#include "GLCamera.h"
#include"math.h"
#include<vector>
namespace OMT
{
	/*======================================================================*/
	Model::Model()
	{
		request_vertex_status();
		request_edge_status();
		request_face_status();
		request_vertex_texcoords2D();
	}
	Model::~Model()
	{
		release_vertex_status();
		release_edge_status();
		release_face_status();
	}
}
/*======================================================================*/
namespace OMP
{
	Model::Model()
	{
		Mesh.request_vertex_status();
		Mesh.request_edge_status();
		Mesh.request_face_status();
	}
	Model::~Model()
	{
		Mesh.release_vertex_status();
		Mesh.release_edge_status();
		Mesh.release_face_status();
	}
	/*======================================================================*/
	bool Model::ReadFile(std::string _fileName)
	{
		bool isRead = false;
		OpenMesh::IO::Options opt;
		if ( OpenMesh::IO::read_mesh(Mesh, _fileName, opt) )
		{
			//read mesh from filename OK!
			isRead = true;
		}
		if(isRead)
		{
			// If the file did not provide vertex normals and mesh has vertex normal ,then calculate them
			if (!opt.check( OpenMesh::IO::Options::VertexNormal ) && Mesh.has_vertex_normals())
			{
				Mesh.update_normals();
			}
		}
		return isRead;
	}
	bool Model::SaveFile(std::string _fileName)
	{
		bool isSave = false;
		OpenMesh::IO::Options opt;
		opt += IO::Options::VertexTexCoord;
		if ( OpenMesh::IO::write_mesh(Mesh, _fileName, opt) )
		{
			//read mesh from filename OK!
			isSave = true;
		}
		return isSave;
	}
	/*======================================================================*/
	void Model::Render_solid()
	{
		FIter f_it;
		FVIter	fv_it;
		glPushAttrib(GL_LIGHTING_BIT);
		glEnable(GL_POLYGON_OFFSET_FILL);
		glEnable(GL_DEPTH_TEST);
		glPolygonOffset(2.0, 2.0);
		glBegin(GL_POLYGON);
		//glColor4f(1.0, 0.5, 1.0, 0.5);
		for (f_it = Mesh.faces_begin(); f_it != Mesh.faces_end(); ++f_it) 
		{
			for (fv_it = Mesh.fv_iter( f_it ); fv_it; ++fv_it)
			{						
				glNormal3dv(Mesh.normal(fv_it.handle()).data());
				glVertex3dv(Mesh.point(fv_it.handle()).data());
			}
		}
		glEnd();		
		glDisable(GL_POLYGON_OFFSET_FILL);
	}
	void Model::Render_wireframe()
	{
		MyMesh::HalfedgeHandle _hedge;
		EIter e_it=Mesh.edges_begin();

		glDisable(GL_LIGHTING);
		glEnable(GL_DEPTH_TEST);
		glColor3f(0.0, 0.0, 0.0);
		glLineWidth(1);
		glBegin(GL_LINES);
		for(e_it=Mesh.edges_begin(); e_it != Mesh.edges_end(); ++e_it)
		{
			_hedge = Mesh.halfedge_handle(e_it.handle(),1);

			glVertex3dv(Mesh.point(Mesh.from_vertex_handle(_hedge)).data());
			glVertex3dv(Mesh.point(Mesh.to_vertex_handle(_hedge)).data());			
		}
		glEnd();
		glEnable(GL_LIGHTING);
	}
	/*======================================================================*/
	void Model::RenderSpecifiedPoint()
	{
		glPushAttrib(GL_LIGHTING_BIT);
		glDisable(GL_LIGHTING);
		glEnable(GL_DEPTH_TEST);
		glPointSize(5.0f);
		glBegin(GL_POINTS);
		vector<sp_p>::iterator p_itr = sp_p_list.begin();
		for (p_itr; p_itr != sp_p_list.end(); ++p_itr)
		{
			glColor3f(p_itr->r, p_itr->g, p_itr->b);
			glVertex3dv(p_itr->pt.data());
		}
		glEnd();
		glEnable(GL_LIGHTING);
		glDisable(GL_POLYGON_OFFSET_FILL);
	}
	void Model::RenderSpecifiedVertex()
	{
		glPushAttrib(GL_LIGHTING_BIT);
		glDisable(GL_LIGHTING);
		glEnable(GL_DEPTH_TEST);
		glPointSize(5.0f);
		glBegin(GL_POINTS);
		vector< sp_v >::iterator v_itr = sp_v_list.begin();
		for (v_itr; v_itr != sp_v_list.end(); ++v_itr)
		{
			glColor3f(v_itr->r, v_itr->g, v_itr->b);
			glVertex3dv(Mesh.point(v_itr->vh).data());
		}
		glEnd();
		glEnable(GL_LIGHTING);
		glDisable(GL_POLYGON_OFFSET_FILL);
	}
	void Model::RenderSpecifiedFace()
	{
		glDisable(GL_CULL_FACE);
		glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
		glPushAttrib(GL_LIGHTING_BIT);
		glEnable(GL_POLYGON_OFFSET_FILL);
		glPolygonOffset(0.5, 1.0);
		glDisable(GL_LIGHTING);
		glEnable(GL_DEPTH_TEST);
		glBegin(GL_QUADS);
		FVIter fv_itr;
		vector< sp_f >::iterator f_itr;
		for (f_itr = sp_f_list.begin(); f_itr != sp_f_list.end(); ++f_itr)
		{
			glColor3f(f_itr->r, f_itr->g, f_itr->b);
			for (fv_itr=Mesh.fv_iter(f_itr->fh); fv_itr; ++fv_itr)
			{						
				glNormal3dv(Mesh.normal(fv_itr.handle()).data());
				glVertex3dv(Mesh.point(fv_itr.handle()).data());
			}
		}
		glEnd();		
		glEnable(GL_LIGHTING);
		glDisable(GL_POLYGON_OFFSET_FILL);
		glPolygonMode(GL_FRONT,GL_FILL);
		glEnable(GL_CULL_FACE);
	}

	/*======================================================================*/
	void Model::add_sp_p(Point   _p, float _r, float _g, float _b)
	{
		sp_p input_data;
		input_data.pt = _p;
		input_data.r = _r;
		input_data.g = _g;
		input_data.b = _b;
		sp_p_list.push_back(input_data);
	}
	void Model::add_sp_v(VHandle _v, float _r, float _g, float _b)
	{
		sp_v input_data;
		input_data.vh = _v;
		input_data.r = _r;
		input_data.g = _g;
		input_data.b = _b;
		sp_v_list.push_back(input_data);
	}
	void Model::add_sp_f(FHandle _f, float _r, float _g, float _b)
	{
		sp_f input_data;
		input_data.fh = _f;
		input_data.r = _r;
		input_data.g = _g;
		input_data.b = _b;
		sp_f_list.push_back(input_data);
	}
	void Model::clear_sp_p()
	{
		sp_p_list.clear();
	}
	void Model::clear_sp_v()
	{
		sp_v_list.clear();
	}
	void Model::clear_sp_f()
	{
		sp_f_list.clear();
	}
	/*======================================================================*/
	VHandle Model::addVertex(Point _p)
	{
		int find_result = findVertex(_p);
		if (find_result != -1)
		{
			return Mesh.vertex_handle(find_result);
		}
		else
		{
			return Mesh.add_vertex(_p);
		}
	}
	FHandle Model::addFace(VHandle _v0, VHandle _v1, VHandle _v2, VHandle _v3)
	{
		vector<VHandle> face_vhandles;

		face_vhandles.clear();
		face_vhandles.push_back(_v0);
		face_vhandles.push_back(_v1);
		face_vhandles.push_back(_v2);
		face_vhandles.push_back(_v3);
		return Mesh.add_face(face_vhandles);
	}
	void Model::deleteFace(FHandle _f)
	{
		Mesh.delete_face(_f);
		Mesh.garbage_collection();
	}
	void Model::deleteFace(VHandle _v0, VHandle _v1, VHandle _v2, VHandle _v3)
	{
		/* 
		v1				v0
		*<--------------*
		|				|
		|				|
		|				|
		|		f		|
		|				|
		|				|
		|				|
		* --------------*
		v2				v3
		*/

		HEHandle v0v1 = Mesh.find_halfedge(_v0, _v1);
		if (v0v1.is_valid())
		{
			FHandle fh = Mesh.face_handle(v0v1);
			if (fh.is_valid())
			{
				Mesh.delete_face(fh);
				Mesh.garbage_collection();
			}
		}
	}
	/*======================================================================*/
	bool Model::IsVertexVertex( VHandle _vj, VHandle _vi)
	{
		for( VVIter vvit = Mesh.vv_iter(_vi) ; vvit ; ++vvit )
			if( vvit.handle() == _vj )
				return true;
		return false;
	}
	/*======================================================================*/
	int Model::quad_subdivision1(int _face_id)
	{
		/*----------------------------------------------------------------------*/
		//這段是為了解決index問題
		VHandle vq, vw, vt, vr;
		vq	 = addVertex(Point(0, 0, 100));
		vw	 = addVertex(Point(1, 0, 100));
		vt	 = addVertex(Point(1, 1, 100));
		vr	 = addVertex(Point(0, 1, 100));
		addFace(vq, vw, vt, vr);
		/*----------------------------------------------------------------------*/
		/*收集需要subdivision的face*/
		//初始table
		bool *table = new bool[Mesh.n_faces()];
		for (unsigned i = 0; i < Mesh.n_faces(); i++)
		{
			table[i] = false;
		}

		vector< FHandle > candidate_faces, last_found_face;
		last_found_face.push_back(Mesh.face_handle(_face_id));
		table[_face_id] = true;

		while(last_found_face.size() != 0)
		{
			vector< FHandle > new_found_faces;
			for (vector< FHandle >::iterator crnt_f = last_found_face.begin(); crnt_f != last_found_face.end(); ++crnt_f)
			{
				for (FFIter ff_itr = Mesh.ff_iter(*crnt_f); ff_itr; ++ff_itr)
				{
					if (table[ff_itr.handle().idx()] != true)
					{
						new_found_faces.push_back(ff_itr.handle());
						table[ff_itr.handle().idx()] = true;
					}
				}
			}
			for (vector< FHandle >::iterator f_itr = last_found_face.begin(); f_itr != last_found_face.end(); ++f_itr)
			{
				candidate_faces.push_back(*f_itr);
			}
			last_found_face.assign(new_found_faces.begin(), new_found_faces.end());
		}
		delete table;
		/*----------------------------------------------------------------------*/
		/*對candidate faces做subdivision*/
		/*
			v0		vd		v3
			*-------*-------*
			|		|		|	 
			|		|		|
			|	  ve|		|
		  va*-------*-------*vc
			|		|		|
			|		|		|
			|		|		|
			*-------*-------*
			v1		vb		v2		
		*/
		for (vector< FHandle >::iterator face_itr = candidate_faces.begin(); face_itr != candidate_faces.end(); ++face_itr)
		{
			VHandle v[4], va, vb, vc, vd, ve;
			FVIter fv_itr = Mesh.fv_iter(*face_itr);
			for (int i = 0; fv_itr; ++fv_itr)
			{
				v[i++] = fv_itr.handle();
			}

			deleteFace(v[0], v[1], v[2], v[3]);
			va	 = addVertex((Mesh.point(v[0])+Mesh.point(v[1]))/2);
			vb	 = addVertex((Mesh.point(v[1])+Mesh.point(v[2]))/2);
			vc	 = addVertex((Mesh.point(v[2])+Mesh.point(v[3]))/2);
			vd	 = addVertex((Mesh.point(v[3])+Mesh.point(v[0]))/2);
			ve	 = addVertex((Mesh.point(v[0])+Mesh.point(v[1])+Mesh.point(v[2])+Mesh.point(v[3]))/4);
			addFace(vd, v[0], va, ve);
			addFace(va, v[1], vb, ve);
			addFace(vb, v[2], vc, ve);
			addFace(vc, v[3], vd, ve);
		}
		/*----------------------------------------------------------------------*/
		deleteFace(vq, vw, vt, vr);//這行只是為了解決index問題
		/*----------------------------------------------------------------------*/
		return 0;
	}
	int Model::quad_subdivision2(int _face_id)
	{
		/*----------------------------------------------------------------------*/
		//這段是為了解決index問題
		VHandle vq, vw, vt, vr;
		vq	 = addVertex(Point(0, 0, 100));
		vw	 = addVertex(Point(1, 0, 100));
		vt	 = addVertex(Point(1, 1, 100));
		vr	 = addVertex(Point(0, 1, 100));
		addFace(vq, vw, vt, vr);
		/*----------------------------------------------------------------------*/
		/*收集需要subdivision的face*/
		//初始table
		bool *table = new bool[Mesh.n_faces()];
		for (unsigned i = 0; i < Mesh.n_faces(); i++)
		{
			table[i] = false;
		}

		vector< FHandle > candidate_faces, last_found_face;
		last_found_face.push_back(Mesh.face_handle(_face_id));
		table[_face_id] = true;

		while(last_found_face.size() != 0)
		{
			vector< FHandle > new_found_faces;
			for (vector< FHandle >::iterator crnt_f = last_found_face.begin(); crnt_f != last_found_face.end(); ++crnt_f)
			{
				for (FFIter ff_itr = Mesh.ff_iter(*crnt_f); ff_itr; ++ff_itr)
				{
					if (table[ff_itr.handle().idx()] != true)
					{
						new_found_faces.push_back(ff_itr.handle());
						table[ff_itr.handle().idx()] = true;
					}
				}
			}
			for (vector< FHandle >::iterator f_itr = last_found_face.begin(); f_itr != last_found_face.end(); ++f_itr)
			{
				candidate_faces.push_back(*f_itr);
			}
			last_found_face.assign(new_found_faces.begin(), new_found_faces.end());
		}
		delete table;
		/*----------------------------------------------------------------------*/
		/*對candidate faces做subdivision*/
		/*
			v0		vh		vg		v3
			*-------*-------*-------*
			|		|		|		|
			|		|		|		|
			|	  vi|	  vl|		|
		 va *-------*-------*-------*vf
			|		|		|		|
			|		|		|		|
			|	  vj|	  vk|		|
		 vb *-------*-------*-------*ve
			|		|		|		|
			|		|		|		|
			|		|		|		|
			*-------*-------*-------*
			v1		vc		vd		v2		
		*/
		for (vector< FHandle >::iterator face_itr = candidate_faces.begin(); face_itr != candidate_faces.end(); ++face_itr)
		{
			VHandle v[4], va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl;
			FVIter fv_itr = Mesh.fv_iter(*face_itr);
			for (int i = 0; fv_itr; ++fv_itr)
			{
				v[i++] = fv_itr.handle();
			}

			deleteFace(v[0], v[1], v[2], v[3]);
			va	 = addVertex((Mesh.point(v[0])*2+Mesh.point(v[1])  )/3);
			vb	 = addVertex((Mesh.point(v[0])  +Mesh.point(v[1])*2)/3);
			vc	 = addVertex((Mesh.point(v[1])*2+Mesh.point(v[2])  )/3);
			vd	 = addVertex((Mesh.point(v[1])  +Mesh.point(v[2])*2)/3);
			ve	 = addVertex((Mesh.point(v[2])*2+Mesh.point(v[3])  )/3);
			vf	 = addVertex((Mesh.point(v[2])  +Mesh.point(v[3])*2)/3);
			vg	 = addVertex((Mesh.point(v[3])*2+Mesh.point(v[0])  )/3);
			vh	 = addVertex((Mesh.point(v[3])  +Mesh.point(v[0])*2)/3);

			vi	 = addVertex((Mesh.point(vh)*2+Mesh.point(vc)  )/3);
			vj	 = addVertex((Mesh.point(vh)  +Mesh.point(vc)*2)/3);
			vk	 = addVertex((Mesh.point(vd)*2+Mesh.point(vg)  )/3);
			vl	 = addVertex((Mesh.point(vd)  +Mesh.point(vg)*2)/3);
			addFace(v[0], va, vi, vh);
			addFace(va, vb, vj, vi);
			addFace(vb, v[1], vc, vj);
			addFace(vc, vd, vk, vj);
			addFace(vd, v[2], ve, vk);
			addFace(ve, vf, vl, vk);
			addFace(vf, v[3], vg, vl);
			addFace(vg, vh, vi, vl);
			addFace(vi, vj, vk, vl);
		}
		/*----------------------------------------------------------------------*/
		deleteFace(vq, vw, vt, vr);//這行只是為了解決index問題
		/*----------------------------------------------------------------------*/
		return 0;
	}
	/*======================================================================*/
	int Model::findVertex(Point _p)
	{
		for( VIter v_itr = Mesh.vertices_begin(); v_itr != Mesh.vertices_end(); ++v_itr)
			if( Mesh.point(v_itr) == _p )
				return v_itr.handle().idx();
		return -1;
	}
	/*======================================================================*/
};
/*======================================================================*/
void Tri_Mesh::Render_Solid()
{
		FIter f_it;
		FVIter	fv_it;
		//glPushAttrib(GL_LIGHTING_BIT);
		glEnable(GL_POLYGON_OFFSET_FILL);
		glEnable(GL_LIGHTING);
		glPolygonOffset(2.0, 2.0);
		glBegin(GL_TRIANGLES);
		glColor4f(0.81, 0.74, 0.33, 0.3);
		for (f_it = faces_begin(); f_it != faces_end(); ++f_it) 
		{
			for (fv_it = fv_iter( f_it ); fv_it; ++fv_it)
			{						
				glNormal3dv(normal(fv_it.handle()).data());
				glVertex3dv(point(fv_it.handle()).data());
			}
		}
		glEnd();	
		
		glDisable(GL_POLYGON_OFFSET_FILL);
}

void Tri_Mesh::Render_SolidWireframe()
{
	FIter f_it;
	FVIter	fv_it;

	
	/*glPointSize(8.0);
	glBegin(GL_POINTS);
	glColor4f(1.0, 0.0, 0.0, 1.0);
	glVertex3dv(point(vertex_handle(0)));
	glEnd();*/
    glDisable(GL_LIGHTING);
	glPushAttrib(GL_LIGHTING_BIT);
	glEnable(GL_POLYGON_OFFSET_FILL);
	glEnable(GL_DEPTH_TEST);
	glPolygonOffset(2.0, 2.0);
	glBegin(GL_TRIANGLES);
	glColor4f(1.0, 0.96, 0.49, 1.0);
	for (f_it = faces_begin(); f_it != faces_end(); ++f_it) 
	{
		for (fv_it = fv_iter( f_it ); fv_it; ++fv_it)
		{						
			//glNormal3dv(normal(fv_it.handle()));
			glVertex3dv(point(fv_it.handle()).data());
		}
	}
	glEnd();

	
	//glDisable(GL_POLYGON_OFFSET_FILL);


	glPushAttrib(GL_LIGHTING_BIT);	
	glDisable(GL_LIGHTING);
	glLineWidth(1.0);
	glColor3f(0.0, 0.0, 0.0);	
	glBegin(GL_LINES);
	for(OMT::EIter e_it = edges_begin(); e_it != edges_end(); ++e_it)
	{
		OMT::HEHandle _hedge = halfedge_handle(e_it.handle(),1);

		OMT::Point curVertex  = point(from_vertex_handle(_hedge));
		glVertex3dv(curVertex.data());

		curVertex = point(to_vertex_handle(_hedge));
		glVertex3dv(curVertex.data());			
	}
	glEnd();
	glPopAttrib();



}

void Tri_Mesh::Render_Wireframe()
{
	//glPushAttrib(GL_LIGHTING_BIT);	
	glDisable(GL_LIGHTING);
	glLineWidth(1.0);
	
	glColor3f(0.0, 0.0, 0.0);	

	glBegin(GL_LINES);
	for(OMT::EIter e_it = edges_begin(); e_it != edges_end(); ++e_it)
	{
		OMT::HEHandle _hedge = halfedge_handle(e_it.handle(),1);

		OMT::Point curVertex  = point(from_vertex_handle(_hedge));
		glVertex3dv(curVertex.data());

		curVertex = point(to_vertex_handle(_hedge));
		glVertex3dv(curVertex.data());			
	}
	glEnd();
	
}

void Tri_Mesh::Render_Point()
{
	glPointSize ( 8.0 ) ;				  
	glColor3f( 1.0, 0.0, 0.0 ) ;
	glBegin(GL_POINTS);
	for (OMT::VIter v_it = vertices_begin() ; v_it != vertices_end() ; ++v_it)
	{
		  glVertex3dv(point(v_it).data());
	}
	
	glEnd();
}

OMT::VertexHandle Tri_Mesh::findpoint(float x, float y, float z)
{
	FIter f_it;
	FVIter	fv_it;
	double distance = 999999999.0;
	double tempdistance;
	OMT::Point temppoint;
	OMT::Point finalpoint;
	OMT::VertexHandle r_vh;
	
	for (f_it = faces_begin(); f_it != faces_end(); ++f_it)
	{
		for (fv_it = fv_iter(f_it); fv_it; ++fv_it)
		{			
			temppoint = point(fv_it.handle());
			tempdistance = sqrt(pow((double)(x) - temppoint[0], 2) + pow((double)(y) - temppoint[1], 2) + pow((double)(z) - temppoint[2], 2));
			
			if (tempdistance < distance)
			{
				finalpoint = temppoint;
				distance = tempdistance;
				r_vh = fv_it.handle();
			}
		}
	}
	return r_vh;
	

}

std::vector<OMT::VertexHandle> Tri_Mesh::mouse_pick_face_vh(double x, double y, double z)
{
	FIter f_it;
	FVIter	fv_it;
	VFIter  vf_it;
	double temparea;
	double area = 100;
	double areaAMB, areaBMC, areaCMA, areaABC;
	double edgeAB, edgeBC, edgeCA, edgeAM, edgeBM, edgeCM;  // triangle ABC  mousepoint M
	OMT::Point temppoint;
	double distance = 10000;
	double tempdistance;
	int repeat = 0;
	
	for (f_it = faces_begin(); f_it != faces_end(); ++f_it)//find nearest point
	{
		for (fv_it = fv_iter(f_it); fv_it; ++fv_it)
		{
			temppoint = point(fv_it.handle());
			tempdistance = sqrt(pow(x - temppoint[0], 2) + pow(y - temppoint[1], 2) + pow(z - temppoint[2], 2));

			if (tempdistance < distance)
			{
				tempfv_it = fv_it;
				distance = tempdistance;
			}
		}
	}

	OMT::FaceHandle r_fh;
	for (vf_it = vf_iter(tempfv_it); vf_it; ++vf_it)
	{
		int count = 0;

		for (fv_it = fv_iter(vf_it); fv_it; ++fv_it)
		{
			switch (count)
			{
			case 0:
				pointA = point(fv_it.handle());
				count++;
				break;
			case 1:
				pointB = point(fv_it.handle());
				count++;
				break;
			case 2:
				pointC = point(fv_it.handle());
				break;
			}
		}

		edgeAB = sqrt(pow(pointB[0] - pointA[0], 2) + pow(pointB[1] - pointA[1], 2) + pow(pointB[2] - pointA[2], 2));
		edgeBC = sqrt(pow(pointB[0] - pointC[0], 2) + pow(pointB[1] - pointC[1], 2) + pow(pointB[2] - pointC[2], 2));
		edgeCA = sqrt(pow(pointC[0] - pointA[0], 2) + pow(pointC[1] - pointA[1], 2) + pow(pointC[2] - pointA[2], 2));
		edgeAM = sqrt(pow(x - pointA[0], 2) + pow(y - pointA[1], 2) + pow(z - pointA[2], 2));
		edgeBM = sqrt(pow(x - pointB[0], 2) + pow(y - pointB[1], 2) + pow(z - pointB[2], 2));
		edgeCM = sqrt(pow(x - pointC[0], 2) + pow(y - pointC[1], 2) + pow(z - pointC[2], 2));
		areaAMB = sqrt((edgeAB + edgeBM + edgeAM)*0.5*((edgeAB + edgeBM + edgeAM)*0.5 - edgeAB)*((edgeAB + edgeBM + edgeAM)*0.5 - edgeBM)*((edgeAB + edgeBM + edgeAM)*0.5 - edgeAM));
		areaBMC = sqrt((edgeBC + edgeBM + edgeCM)*0.5*((edgeBC + edgeBM + edgeCM)*0.5 - edgeBC)*((edgeBC + edgeBM + edgeCM)*0.5 - edgeBM)*((edgeBC + edgeBM + edgeCM)*0.5 - edgeCM));
		areaCMA = sqrt((edgeCA + edgeCM + edgeAM)*0.5*((edgeCA + edgeCM + edgeAM)*0.5 - edgeCA)*((edgeCA + edgeCM + edgeAM)*0.5 - edgeCM)*((edgeCA + edgeCM + edgeAM)*0.5 - edgeAM));
		areaABC = sqrt((edgeAB + edgeBC + edgeCA)*0.5*((edgeAB + edgeBC + edgeCA)*0.5 - edgeAB)*((edgeAB + edgeBC + edgeCA)*0.5 - edgeBC)*((edgeAB + edgeBC + edgeCA)*0.5 - edgeCA));
		temparea = areaAMB + areaBMC + areaCMA - areaABC;

		if (abs(temparea) < area)
		{
			area = abs(temparea);
			r_fh = vf_it.handle();
		}

	}
	
	if (pick_face_firsttimecount != 1)
	{
		pickface_vh.clear();
		for (fv_it=fv_iter(r_fh); fv_it; fv_it++)
		{
			pickface_vh.push_back(fv_it.handle());
			
		}
		
		pick_face_firsttimecount = 1;
	}
	else 
	{
		for (fv_it = fv_iter(r_fh); fv_it; fv_it++)
		{	
			repeat = 0;
			for (int i = 0; i < pickface_vh.size(); i++)
			{
				if (pickface_vh[i] == fv_it.handle())
				{
					repeat = 1;
					break;
				}
			}
			
			if (repeat != 1)
			{
				pickface_vh.push_back(fv_it.handle());
				repeat = 0;
			}
		}	
	}
	


	return pickface_vh;

}

std::vector<OMT::VertexHandle> Tri_Mesh::copy_point_repeat(std::vector<OMT::VertexHandle> copyvh,OMT::FaceHandle newfh)
{
	int repeat = 0;
	FVIter fv_it;
	OMT::VertexHandle repeat_vhA;
	OMT::VertexHandle repeat_vhB;
	OMT::VertexHandle repeat_vhC;
	std::vector<OMT::VertexHandle> returnvh;
	returnvh.clear();
	
		for (fv_it = fv_iter(newfh); fv_it; fv_it++)
		{
			int put_new = 1;
			for (int i = 0; i < copyvh.size(); i++)
			{
				if (repeat == 0)
				{
					if (fv_it.handle() == copyvh[i])
					{
						repeat_vhA = fv_it.handle();
						repeat = 1;
						put_new = 0;
						break;
					}
				}
				else if (repeat == 1)
				{
					if (fv_it.handle() == copyvh[i])
					{
						repeat_vhB = fv_it.handle();
						repeat = 2;
						put_new = 0;
						break;
					}
				}
				else if (repeat == 2)
				{
					if (fv_it.handle() == copyvh[i])
					{
						repeat_vhC = fv_it.handle();
						repeat = 3;
						put_new = 0;
						break;
					}
				}

			}
			if (put_new == 1)
			{
				repeat_vhC = fv_it.handle();
			}
		}
	
		
	
	returnvh.push_back(repeat_vhA);
	returnvh.push_back(repeat_vhB);
	returnvh.push_back(repeat_vhC);

	return returnvh;

}

std::vector<OMT::FaceHandle> Tri_Mesh::mouse_pick_roundface(double x, double y, double z)
{
	FIter f_it;
	FVIter	fv_it;
	VFIter  vf_it;
	OMT::Point temppoint;
	double distance = 10000;
	double tempdistance;
	int repeat = 0;

	for (f_it = faces_begin(); f_it != faces_end(); ++f_it)//find nearest point
	{
		for (fv_it = fv_iter(f_it); fv_it; ++fv_it)
		{
			temppoint = point(fv_it.handle());
			tempdistance = sqrt(pow(x - temppoint[0], 2) + pow(y - temppoint[1], 2) + pow(z - temppoint[2], 2));

			if (tempdistance < distance)
			{
				if (tempdistance < 0.06)
				{
					tempfv_it = fv_it;
					distance = tempdistance;
				}
			}
		}
	}
	middlepoint_v_h = tempfv_it.handle();
	
	pickroundface_h.clear();
	pickroundfacecount = 0;
	for (vf_it = vf_iter(tempfv_it); vf_it; ++vf_it)
	{
		pickroundface_h.push_back(vf_it.handle());
		pickroundfacecount++;
	}


	return pickroundface_h;

}


OMT::FaceHandle Tri_Mesh::findface(double x, double y, double z)
{
	FIter   f_it;
	VFIter  vf_it;
	FVIter	fv_it;
	double temparea;
	double area = 999999.0;
	double areaAMB, areaBMC, areaCMA, areaABC;
	double edgeAB, edgeBC, edgeCA, edgeAM, edgeBM, edgeCM;  // triangle ABC  mousepoint M
	double distance = 10000;
	double tempdistance;
	OMT::Point temppoint;
	


	for (f_it = faces_begin(); f_it != faces_end(); ++f_it)//find nearest point
	{
		for (fv_it = fv_iter(f_it); fv_it; ++fv_it)
		{
			temppoint = point(fv_it.handle());
			tempdistance = sqrt(pow(x - temppoint[0], 2) + pow(y - temppoint[1], 2) + pow(z - temppoint[2], 2));

			if (tempdistance < distance)
			{
				tempfv_it = fv_it;
				distance = tempdistance;
			}
		}
	}

	OMT::FaceHandle r_fh;
	for (vf_it = vf_iter(tempfv_it); vf_it; ++vf_it)
	{
		int count = 0;
		for (fv_it = fv_iter(vf_it); fv_it; ++fv_it)
		{
			switch (count)
			{
			case 0:
				pointA = point(fv_it.handle());
				count++;
				break;
			case 1:
				pointB = point(fv_it.handle());
				count++;
				break;
			case 2:
				pointC = point(fv_it.handle());
				break;
			}
		}
		/*double vectorAM[3] = { x - pointA[0] ,y - pointA[1] ,z - pointA[2] };
		double vectorBM[3] = { x - pointB[0] ,y - pointB[1] ,z - pointB[2] };
		double vectorCM[3] = { x - pointC[0] ,y - pointC[1] ,z - pointC[2] };

		double vectorAB[3] = { pointB[0] - pointA[0] ,pointB[1] - pointA[1] ,pointB[2] - pointA[2] };
		double vectorAC[3] = { pointC[0] - pointA[0] ,pointC[1] - pointA[1] ,pointC[2] - pointA[2] };
		double crossvectorABAC[3]{ vectorAB[1] * vectorAC[2] - vectorAC[1] * vectorAB[2],
								vectorAB[2] * vectorAC[0] - vectorAC[2] * vectorAB[0],
								vectorAB[0] * vectorAC[1] - vectorAC[0] * vectorAB[1] };
		double crossvectorABAM[3]{ vectorAB[1] * vectorAM[2] - vectorAM[1] * vectorAB[2],
								vectorAB[2] * vectorAM[0] - vectorAM[2] * vectorAB[0],
								vectorAB[0] * vectorAM[1] - vectorAM[0] * vectorAB[1] };
		double dot1 = crossvectorABAC[0] * crossvectorABAM[0] + crossvectorABAC[1] * crossvectorABAM[1] + crossvectorABAC[2] * crossvectorABAM[2];

		double vectorBC[3] = { pointC[0] - pointB[0] ,pointC[1] - pointB[1] ,pointC[2] - pointB[2] };
		double vectorBA[3] = { pointA[0] - pointB[0] ,pointA[1] - pointB[1] ,pointA[2] - pointB[2] };
		double crossvectorBCBA[3]{ vectorBC[1] * vectorBA[2] - vectorBA[1] * vectorBC[2],
								vectorBC[2] * vectorBA[0] - vectorBA[2] * vectorBC[0],
								vectorBC[0] * vectorBA[1] - vectorBA[0] * vectorBC[1] };
		double crossvectorBCBM[3]{ vectorBC[1] * vectorBM[2] - vectorBM[1] * vectorBM[2],
								vectorBC[2] * vectorBM[0] - vectorBM[2] * vectorBM[0],
								vectorBC[0] * vectorBM[1] - vectorBM[0] * vectorBM[1] };
		double dot2 = crossvectorBCBA[0] * crossvectorBCBM[0] + crossvectorBCBA[1] * crossvectorBCBM[1] + crossvectorBCBA[2] * crossvectorBCBM[2];

		double vectorCA[3] = { pointA[0] - pointC[0] ,pointA[1] - pointC[1] ,pointA[2] - pointC[2] };
		double vectorCB[3] = { pointB[0] - pointC[0] ,pointB[1] - pointC[1] ,pointB[2] - pointC[2] };
		double crossvectorCACB[3]{ vectorCA[1] * vectorCB[2] - vectorCB[1] * vectorCA[2],
								vectorCA[2] * vectorCB[0] - vectorCB[2] * vectorCA[0],
								vectorCA[0] * vectorCB[1] - vectorCB[0] * vectorCA[1] };
		double crossvectorCACM[3]{ vectorCA[1] * vectorCM[2] - vectorCM[1] * vectorCM[2],
								vectorCA[2] * vectorCM[0] - vectorCM[2] * vectorCM[0],
								vectorCA[0] * vectorCM[1] - vectorCM[0] * vectorCM[1] };
		double dot3 = crossvectorCACB[0] * crossvectorCACM[0] + crossvectorCACB[1] * crossvectorCACM[1] + crossvectorCACB[2] * crossvectorCACM[2];

		if (dot1 >= 0 && dot2 >= 0 && dot3 >= 0)
		{
			r_fh = vf_it.handle();
		}

*/



/*double vectorAB[3] = { pointB[0] - pointA[0] ,pointB[1] - pointA[1] ,pointB[2] - pointA[2] };
double vectorAC[3] = { pointC[0] - pointA[0] ,pointC[1] - pointA[1] ,pointC[2] - pointA[2] };
double vectorMA[3] = { pointA[0] - x ,pointA[1] - y ,pointA[2] - z };
double vectorMB[3] = { pointB[0] - x ,pointB[1] - y ,pointB[2] - z };
double vectorMC[3] = { pointC[0] - x ,pointC[1] - y ,pointC[2] - z };

double crossvectorABAC[3]{ vectorAB[1] * vectorAC[2] - vectorAC[1] * vectorAB[2],
						vectorAB[2] * vectorAC[0] - vectorAC[2] * vectorAB[0],
						vectorAB[0] * vectorAC[1] - vectorAC[0] * vectorAB[1] };

double crossvectorMBMC[3]{ vectorMB[1] * vectorMC[2] - vectorMC[1] * vectorMB[2],
						vectorMB[2] * vectorMC[0] - vectorMC[2] * vectorMB[0],
						vectorMB[0] * vectorMC[1] - vectorMC[0] * vectorMB[1] };

double crossvectorMCMA[3]{ vectorMC[1] * vectorMA[2] - vectorMA[1] * vectorMC[2],
						vectorMC[2] * vectorMA[0] - vectorMA[2] * vectorMC[0],
						vectorMC[0] * vectorMA[1] - vectorMA[0] * vectorMC[1] };
double A = sqrt(pow(crossvectorABAC[0], 2) + pow(crossvectorABAC[1], 2) + pow(crossvectorABAC[2], 2))*0.5;
double alpha = sqrt(pow(crossvectorMBMC[0], 2) + pow(crossvectorMBMC[1], 2) + pow(crossvectorMBMC[2], 2))*0.5 / A;
double beta = sqrt(pow(crossvectorMCMA[0], 2) + pow(crossvectorMCMA[1], 2) + pow(crossvectorMCMA[2], 2))*0.5 / A;
double garma = 1.0 - alpha - beta;
*/
/*
if (alpha >= 0 && alpha <= 1 && beta >= 0 && beta <= 1 && garma >= 0 && garma <= 1)
{
	std::cout << alpha<<"  "<<beta<<"  "<<garma << std::endl;
	r_fh = vf_it.handle();
}*/


		edgeAB = sqrt(pow(pointB[0] - pointA[0], 2) + pow(pointB[1] - pointA[1], 2) + pow(pointB[2] - pointA[2], 2));
		edgeBC = sqrt(pow(pointB[0] - pointC[0], 2) + pow(pointB[1] - pointC[1], 2) + pow(pointB[2] - pointC[2], 2));
		edgeCA = sqrt(pow(pointC[0] - pointA[0], 2) + pow(pointC[1] - pointA[1], 2) + pow(pointC[2] - pointA[2], 2));
		edgeAM = sqrt(pow(x - pointA[0], 2) + pow(y - pointA[1], 2) + pow(z - pointA[2], 2));
		edgeBM = sqrt(pow(x - pointB[0], 2) + pow(y - pointB[1], 2) + pow(z - pointB[2], 2));
		edgeCM = sqrt(pow(x - pointC[0], 2) + pow(y - pointC[1], 2) + pow(z - pointC[2], 2));
		areaAMB = sqrt((edgeAB + edgeBM + edgeAM)*0.5*((edgeAB + edgeBM + edgeAM)*0.5 - edgeAB)*((edgeAB + edgeBM + edgeAM)*0.5 - edgeBM)*((edgeAB + edgeBM + edgeAM)*0.5 - edgeAM));
		areaBMC = sqrt((edgeBC + edgeBM + edgeCM)*0.5*((edgeBC + edgeBM + edgeCM)*0.5 - edgeBC)*((edgeBC + edgeBM + edgeCM)*0.5 - edgeBM)*((edgeBC + edgeBM + edgeCM)*0.5 - edgeCM));
		areaCMA = sqrt((edgeCA + edgeCM + edgeAM)*0.5*((edgeCA + edgeCM + edgeAM)*0.5 - edgeCA)*((edgeCA + edgeCM + edgeAM)*0.5 - edgeCM)*((edgeCA + edgeCM + edgeAM)*0.5 - edgeAM));
		areaABC = sqrt((edgeAB + edgeBC + edgeCA)*0.5*((edgeAB + edgeBC + edgeCA)*0.5 - edgeAB)*((edgeAB + edgeBC + edgeCA)*0.5 - edgeBC)*((edgeAB + edgeBC + edgeCA)*0.5 - edgeCA));
		temparea = areaAMB + areaBMC + areaCMA - areaABC;

		if (abs(temparea) < area)
		{
			area = abs(temparea);
			r_fh = vf_it.handle();
		}
	}
	return r_fh;
}

std::vector<OMT::FaceHandle> Tri_Mesh::mouse_pick_face(double x, double y, double z)
{
	
	FIter f_it;
	FVIter	fv_it;
	VFIter  vf_it;
	double temparea;
	double area = 99999999.0;
	double areaAMB, areaBMC, areaCMA, areaABC;
	double edgeAB, edgeBC, edgeCA, edgeAM, edgeBM, edgeCM;  // triangle ABC  mousepoint M
	OMT::Point temppoint;
	double distance = 10000;
	double tempdistance;
	int repeat = 0;
	for (f_it = faces_begin(); f_it != faces_end(); ++f_it)//find nearest point
	{
		for (fv_it = fv_iter(f_it); fv_it; ++fv_it)
		{
			temppoint = point(fv_it.handle());
			tempdistance = sqrt(pow(x - temppoint[0], 2) + pow(y - temppoint[1], 2) + pow(z - temppoint[2], 2));

			if (tempdistance < distance)
			{
				tempfv_it = fv_it;
				distance = tempdistance;
			}
		}
	}

	OMT::FaceHandle r_fh;
	for (vf_it = vf_iter(tempfv_it); vf_it; ++vf_it)
	{
		int count = 0;
		
		for (fv_it = fv_iter(vf_it); fv_it; ++fv_it)
		{
			switch (count)
			{
			case 0:
				pointA = point(fv_it.handle());
				count++;
				break;
			case 1:
				pointB = point(fv_it.handle());
				count++;
				break;
			case 2:
				pointC = point(fv_it.handle());
				break;
			}
		}

		edgeAB = sqrt(pow(pointB[0] - pointA[0], 2) + pow(pointB[1] - pointA[1], 2) + pow(pointB[2] - pointA[2], 2));
		edgeBC = sqrt(pow(pointB[0] - pointC[0], 2) + pow(pointB[1] - pointC[1], 2) + pow(pointB[2] - pointC[2], 2));
		edgeCA = sqrt(pow(pointC[0] - pointA[0], 2) + pow(pointC[1] - pointA[1], 2) + pow(pointC[2] - pointA[2], 2));
		edgeAM = sqrt(pow(x - pointA[0], 2) + pow(y - pointA[1], 2) + pow(z - pointA[2], 2));
		edgeBM = sqrt(pow(x - pointB[0], 2) + pow(y - pointB[1], 2) + pow(z - pointB[2], 2));
		edgeCM = sqrt(pow(x - pointC[0], 2) + pow(y - pointC[1], 2) + pow(z - pointC[2], 2));
		areaAMB = sqrt((edgeAB + edgeBM + edgeAM)*0.5*((edgeAB + edgeBM + edgeAM)*0.5 - edgeAB)*((edgeAB + edgeBM + edgeAM)*0.5 - edgeBM)*((edgeAB + edgeBM + edgeAM)*0.5 - edgeAM));
		areaBMC = sqrt((edgeBC + edgeBM + edgeCM)*0.5*((edgeBC + edgeBM + edgeCM)*0.5 - edgeBC)*((edgeBC + edgeBM + edgeCM)*0.5 - edgeBM)*((edgeBC + edgeBM + edgeCM)*0.5 - edgeCM));
		areaCMA = sqrt((edgeCA + edgeCM + edgeAM)*0.5*((edgeCA + edgeCM + edgeAM)*0.5 - edgeCA)*((edgeCA + edgeCM + edgeAM)*0.5 - edgeCM)*((edgeCA + edgeCM + edgeAM)*0.5 - edgeAM));
		areaABC = sqrt((edgeAB + edgeBC + edgeCA)*0.5*((edgeAB + edgeBC + edgeCA)*0.5 - edgeAB)*((edgeAB + edgeBC + edgeCA)*0.5 - edgeBC)*((edgeAB + edgeBC + edgeCA)*0.5 - edgeCA));
		temparea = areaAMB + areaBMC + areaCMA - areaABC;
		
		if (abs(temparea) < area)
		{
			area = abs(temparea);
			r_fh = vf_it.handle();
		}
		
	}
	
	if (firsttimecount != 1)
	{
		pickface_h.push_back(r_fh);
		pickfacecount++;
		firsttimecount = 1;
	}
	else 
	{
		for (int i = 0; i <= pickfacecount - 1; i++)
		{
			if (pickface_h[i] == r_fh)
			{
				repeat = 1;
				break;
			}
		}
		if (repeat != 1)
		{
			pickface_h.push_back(r_fh);
			pickfacecount++;
			repeat = 0;
		}
	}

		
	return pickface_h;
	
}

OMT::VertexHandle Tri_Mesh::return_middle(double x, double y, double z)
{
	FIter f_it;
	FVIter	fv_it;
	OMT::Point temppoint;
	double distance = 10000;
	double tempdistance;
	int repeat = 0;

	for (f_it = faces_begin(); f_it != faces_end(); ++f_it)//find nearest point
	{
		for (fv_it = fv_iter(f_it); fv_it; ++fv_it)
		{
			temppoint = point(fv_it.handle());
			tempdistance = sqrt(pow(x - temppoint[0], 2) + pow(y - temppoint[1], 2) + pow(z - temppoint[2], 2));

			if (tempdistance < distance)
			{
				if (tempdistance < 0.06)
				{
					tempfv_it = fv_it;
					distance = tempdistance;
				}
			}
		}
	}
	middlepoint_v_h = tempfv_it.handle();
	//std::cout << "middle point coordinate" << point(middlepoint_v_h)[0] << "  " << point(middlepoint_v_h)[1] << "  "<< point(middlepoint_v_h)[2] << std::endl;
	if (middlepoint_v_h.is_valid())
	{
		return middlepoint_v_h;
	}
	
}

OMT::Point Tri_Mesh::compute_middle_2d_vertex(std::vector<OMT::VertexHandle> vh,OMT::VertexHandle mid_vh)
{
	VVIter vv_it;
	OMT::Point pointM = point(mid_vh);
	std::vector<OMT::VertexHandle> temp_vh;
	std::vector<double> weight;
	int point_count = 0;
	for (int i = 0; i < vh.size(); i++)
	{
		temp_vh.push_back(vh[i]);
		point_count++;
	}
	
	
	//--------------------first point---------------------------
	OMT::Point pointA = point(temp_vh[point_count-1]);
	OMT::Point pointB = point(temp_vh[0]);
	OMT::Point pointC = point(temp_vh[1]);

	double vectorAM[3] = { pointM[0] - pointA[0],pointM[1] - pointA[1] ,pointM[2] - pointA[2] };
	double vectorAB[3] = { pointB[0] - pointA[0],pointB[1] - pointA[1] ,pointB[2] - pointA[2] };
	double vectorCM[3] = { pointM[0] - pointC[0],pointM[1] - pointC[1] ,pointM[2] - pointC[2] };
	double vectorCB[3] = { pointB[0] - pointC[0],pointB[1] - pointC[1] ,pointB[2] - pointC[2] };

	double size_AM = sqrt(pow(vectorAM[0], 2) + pow(vectorAM[1], 2) + pow(vectorAM[2], 2));
	double size_AB = sqrt(pow(vectorAB[0], 2) + pow(vectorAB[1], 2) + pow(vectorAB[2], 2));
	double size_CM = sqrt(pow(vectorCM[0], 2) + pow(vectorCM[1], 2) + pow(vectorCM[2], 2));
	double size_CB = sqrt(pow(vectorCB[0], 2) + pow(vectorCB[1], 2) + pow(vectorCB[2], 2));

	double AMdotAB = vectorAM[0] * vectorAB[0] + vectorAM[1] * vectorAB[1] + vectorAM[2] * vectorAB[2];
	double CMdotCB = vectorCM[0] * vectorCB[0] + vectorCM[1] * vectorCB[1] + vectorCM[2] * vectorCB[2];

	double thetaMAB = acos(AMdotAB / (size_AB*size_AM));
	double thetaMCB = acos(CMdotCB / (size_CB*size_CM));

	//std::cout << "thetaMAB    " << thetaMAB << std::endl;
	//std::cout << "thetaMCB    " << thetaMCB << std::endl;

	double cot_thetaMAB = (cos(thetaMAB) / sin(thetaMAB));
	double cot_thetaMCB = (cos(thetaMCB) / sin(thetaMCB));

	/*std::cout << "cosMAB    " << cos(thetaMAB) << std::endl;
	std::cout << "sinMAB    " << sin(thetaMAB) << std::endl;
	std::cout << "cosMCB    " << cos(thetaMCB) << std::endl;
	std::cout << "sinMCB    " << sin(thetaMCB) << std::endl;*/


	double weight_i = cot_thetaMAB + cot_thetaMCB;

	weight.push_back(weight_i);	
	//--------------------first point---------------------------


	for (int i = 1; i < point_count; i++)
	{
		if (i != point_count - 1)
		{
			pointA = point(temp_vh[i - 1]);
			pointB = point(temp_vh[i]);
			pointC = point(temp_vh[i + 1]);

			double vectorAM[3] = { pointM[0] - pointA[0],pointM[1] - pointA[1] ,pointM[2] - pointA[2] };
			double vectorAB[3] = { pointB[0] - pointA[0],pointB[1] - pointA[1] ,pointB[2] - pointA[2] };
			double vectorCM[3] = { pointM[0] - pointC[0],pointM[1] - pointC[1] ,pointM[2] - pointC[2] };
			double vectorCB[3] = { pointB[0] - pointC[0],pointB[1] - pointC[1] ,pointB[2] - pointC[2] };

			double size_AM = sqrt(pow(vectorAM[0], 2) + pow(vectorAM[1], 2) + pow(vectorAM[2], 2));
			double size_AB = sqrt(pow(vectorAB[0], 2) + pow(vectorAB[1], 2) + pow(vectorAB[2], 2));
			double size_CM = sqrt(pow(vectorCM[0], 2) + pow(vectorCM[1], 2) + pow(vectorCM[2], 2));
			double size_CB = sqrt(pow(vectorCB[0], 2) + pow(vectorCB[1], 2) + pow(vectorCB[2], 2));

			double AMdotAB = vectorAM[0] * vectorAB[0] + vectorAM[1] * vectorAB[1] + vectorAM[2] * vectorAB[2];
			double CMdotCB = vectorCM[0] * vectorCB[0] + vectorCM[1] * vectorCB[1] + vectorCM[2] * vectorCB[2];

			double thetaMAB = acos(AMdotAB / (size_AB*size_AM));
			double thetaMCB = acos(CMdotCB / (size_CB*size_CM));

			//std::cout << "thetaMAB    " << thetaMAB << std::endl;
			//std::cout << "thetaMCB    " << thetaMCB << std::endl;

			double cot_thetaMAB = (cos(thetaMAB) / sin(thetaMAB));
			double cot_thetaMCB = (cos(thetaMCB) / sin(thetaMCB));

			/*std::cout << "cosMAB    " << cos(thetaMAB) << std::endl;
			std::cout << "sinMAB    " << sin(thetaMAB) << std::endl;
			std::cout << "cosMCB    " << cos(thetaMCB) << std::endl;
			std::cout << "sinMCB    " << sin(thetaMCB) << std::endl;
*/

			double weight_i = cot_thetaMAB + cot_thetaMCB;

			weight.push_back(weight_i);
		}
		else        //last point
		{
			pointA = point(temp_vh[i - 1]);
			pointB = point(temp_vh[i]);
			pointC = point(temp_vh[0]);

			double vectorAM[3] = { pointM[0] - pointA[0],pointM[1] - pointA[1] ,pointM[2] - pointA[2] };
			double vectorAB[3] = { pointB[0] - pointA[0],pointB[1] - pointA[1] ,pointB[2] - pointA[2] };
			double vectorCM[3] = { pointM[0] - pointC[0],pointM[1] - pointC[1] ,pointM[2] - pointC[2] };
			double vectorCB[3] = { pointB[0] - pointC[0],pointB[1] - pointC[1] ,pointB[2] - pointC[2] };

			double size_AM = sqrt(pow(vectorAM[0], 2) + pow(vectorAM[1], 2) + pow(vectorAM[2], 2));
			double size_AB = sqrt(pow(vectorAB[0], 2) + pow(vectorAB[1], 2) + pow(vectorAB[2], 2));
			double size_CM = sqrt(pow(vectorCM[0], 2) + pow(vectorCM[1], 2) + pow(vectorCM[2], 2));
			double size_CB = sqrt(pow(vectorCB[0], 2) + pow(vectorCB[1], 2) + pow(vectorCB[2], 2));

			double AMdotAB = vectorAM[0] * vectorAB[0] + vectorAM[1] * vectorAB[1] + vectorAM[2] * vectorAB[2];
			double CMdotCB = vectorCM[0] * vectorCB[0] + vectorCM[1] * vectorCB[1] + vectorCM[2] * vectorCB[2];

			double thetaMAB = acos(AMdotAB / (size_AB*size_AM));
			double thetaMCB = acos(CMdotCB / (size_CB*size_CM));

			//std::cout << "thetaMAB    " << thetaMAB << std::endl;
			//std::cout << "thetaMCB    " << thetaMCB << std::endl;

			double cot_thetaMAB = (cos(thetaMAB) / sin(thetaMAB));
			double cot_thetaMCB = (cos(thetaMCB) / sin(thetaMCB));

			//std::cout << "cosMAB    " << cos(thetaMAB) << std::endl;
			//std::cout << "sinMAB    " << sin(thetaMAB) << std::endl;
			//std::cout << "cosMCB    " << cos(thetaMCB) << std::endl;
			//std::cout << "sinMCB    " << sin(thetaMCB) << std::endl;


			double weight_i = cot_thetaMAB + cot_thetaMCB;

			weight.push_back(weight_i);
		}
	}
	//std::cout << "  " << "123" << std::endl;
	double WEIGHT =0;
	for (int i = 0; i < temp_vh.size(); i++)
	{
		WEIGHT += weight[i];
		std::cout << "weight   " << weight[i] << "   " << i << std::endl;
	}
	std::cout << "WEIGHT    " << WEIGHT << std::endl;
	//---------(x) w * p------------
	double wp_x=0;
	for (int i = 0; i < temp_vh.size(); i++)
	{
		OMT::Point tmppoint = point(temp_vh[i]);
		wp_x += weight[i] * tmppoint[0];
	}
	//---------(x) w * p------------
	
	//---------(y) w * p------------
	double wp_y=0;
	for (int i = 0; i < temp_vh.size(); i++)
	{
		OMT::Point tmppoint = point(temp_vh[i]);
		wp_y += weight[i] * tmppoint[1];
	}
	//---------(y) w * p------------

	double mid_x = wp_x / WEIGHT;
	double mid_y = wp_y / WEIGHT;
	//weight compute end
	OMT::Point final_2d_middle_point(mid_x, mid_y, 0);

	return final_2d_middle_point;
}

std::vector<double> Tri_Mesh::turn_2d_point(OMT::VertexHandle mid_vh)
{
	FIter f_it;
	FVIter	fv_it;
	VFIter  vf_it;
	VVIter vv_it;
	std::vector<OMT::VertexHandle> temp_vh;
	int repeat = 0;
	int pointcount = 0;
	//std::cout << "  " << "123456" << std::endl;
	for (vv_it = vv_iter(mid_vh); vv_it.is_valid(); vv_it++)
	{
		//std::cout << vv_it.handle().idx() << "  " << "123456" << std::endl;
		temp_vh.push_back(vv_it.handle());
	}
	
	double surround = 0;
	OMT::Point temppointA;
	OMT::Point temppointB;
	double lengthAB;
	std::vector<double> length;
	std::vector<double> proportion;
	for (int i = 0; i < temp_vh.size(); i++)
	{
		//std::cout << i << "  " << "123456" << std::endl;
		if (i != temp_vh.size() - 1)
		{
			temppointA = point(temp_vh[i]);
			temppointB = point(temp_vh[i + 1]);
			lengthAB = sqrt(pow(temppointA[0] - temppointB[0], 2) + pow(temppointA[1] - temppointB[1], 2) + pow(temppointA[2] - temppointB[2], 2));
			length.push_back(lengthAB);
			surround += lengthAB;
		}
		else
		{
			temppointA = point(temp_vh[i]);
			temppointB = point(temp_vh[0]);
			lengthAB = sqrt(pow(temppointA[0] - temppointB[0], 2) + pow(temppointA[1] - temppointB[1], 2) + pow(temppointA[2] - temppointB[2], 2));
			length.push_back(lengthAB);
			surround += lengthAB;
		}
	}
	for (int i = 0; i < length.size(); i++)
	{
		//std::cout << 4 * length[i] / surround << "  " << "123456" << std::endl;
		proportion.push_back(4 * length[i] / surround);
	}

	return proportion;

}

void Tri_Mesh::Render_Texture(std::string filepath) {

	glEnable(GL_TEXTURE_2D);
	if (loadcount == 0) {
		_textureID = TextureApp::GenTexture(((char *)filepath.c_str()));
		loadcount++;
	}


	glClear(GL_DEPTH_BUFFER_BIT);
	glBindTexture(GL_TEXTURE_2D, _textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glColor4f(1.0, 1.0, 1.0, 1.0);
	glBegin(GL_TRIANGLES);

	for (OMT::FIter f_it = faces_begin(); f_it != faces_end(); ++f_it)
	{
		for (OMT::FVIter fv_it = fv_iter(f_it); fv_it; ++fv_it)
		{
			glNormal3dv(normal(fv_it.handle()).data());
			glTexCoord2f(texcoord2D(fv_it)[0], texcoord2D(fv_it)[1]);
			glVertex3dv(point(fv_it.handle()).data());
		}
	}

	glEnd();
	glDisable(GL_TEXTURE_2D);

}


void Tri_Mesh::clear_vh()
{
	pickface_h.clear();
}


bool ReadFile(std::string _fileName,Tri_Mesh *_mesh)
{
	bool isRead = false;
	OpenMesh::IO::Options opt;
	opt += OpenMesh::IO::Options::VertexTexCoord;
	if ( OpenMesh::IO::read_mesh(*_mesh, _fileName, opt) )
	{
		//read mesh from filename OK!
		isRead = true;
	}
	if(isRead)
	{
		// If the file did not provide vertex normals and mesh has vertex normal ,then calculate them
		if (!opt.check( OpenMesh::IO::Options::VertexNormal ) && _mesh->has_vertex_normals())
		{
			_mesh->update_normals();
		}
	}
	return isRead;
}

bool SaveFile(std::string _fileName, Tri_Mesh *_mesh)
{
	OpenMesh::IO::Options opt;
	opt += OpenMesh::IO::Options::VertexTexCoord;
	bool isSave = false;
	if (OpenMesh::IO::write_mesh(*_mesh, _fileName, opt))
	{
		isSave = true;
	}
	return isSave;
}
