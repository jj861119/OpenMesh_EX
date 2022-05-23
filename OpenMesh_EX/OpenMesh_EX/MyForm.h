#pragma once
#include"TextureApp.h"
#include<iostream>
#include "DotNetUtilities.h"
#include "Mesh/GUA_OM.h"
#include "Mesh/DP.h"
#include "Mesh/GLCamera.h"
#include<vector>
#include"math.h"
#include <Eigen/Sparse>



using namespace Eigen;


point position;
Tri_Mesh *mesh;
Tri_Mesh *copymesh;
Tri_Mesh *mesh_2d;
Tri_Mesh *temp_mesh[100];
Tri_Mesh *done_mesh[100];
GLuint texture[100];
std::string donetexture[100];
int idktexture[100];

int meshnum = 0, curnum, loadedmeshnum = 0, texturenum = 0, loadedtexturenum = 0, donemesh = 0;



GLuint hair4;
GLuint hair1;

xform xf;
GLCamera camera;
OMT::FaceHandle select_fh;
OMT::VertexHandle select_vh;
std::vector<OMT::FaceHandle> select_fh_v;
std::vector<OMT::FaceHandle> select_rfh_v;
std::vector<double> final_proportion;

std::vector<double> copycoordinate;
std::vector<OMT::VertexHandle> copyvh;
std::vector<OMT::FaceHandle> copyfh;
int first_copy_count = 0;
std::vector < OMT::VertexHandle> three_vh;
std::vector < OMT::VertexHandle> const_copyvh;
std::vector<OMT::Point> outside_point;


std::vector<OMT::VertexHandle> vh_v;//2d vh
std::vector<OMT::FaceHandle> fh_v;//2d fh
OMT::VertexHandle mid_vh;
double lengthAB;
std::vector<double> length;
std::vector<double> proportion;
int is_first_point = 0;
OMT::VertexHandle first_point;
std::vector<int> face_order;

float fov = 0.7f;
int mouse_x, mouse_y;
int face_confirm, point_confirm, pick_point_confirm, pick_face_confirm , mouse_pick_roundface_confirm = 0;


static const Mouse::button physical_to_logical_map[] = {
	Mouse::NONE, Mouse::ROTATE, Mouse::MOVEXY, Mouse::MOVEZ,
	Mouse::MOVEZ, Mouse::MOVEXY, Mouse::MOVEXY, Mouse::MOVEXY,
};
Mouse::button Mouse_State = Mouse::ROTATE;



namespace OpenMesh_EX {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// MyForm 的摘要
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO:  在此加入建構函式程式碼
			//
		}

	protected:
		/// <summary>
		/// 清除任何使用中的資源。
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  fileToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  loadModelToolStripMenuItem;
	private: System::Windows::Forms::OpenFileDialog^  openModelDialog;
	private: System::Windows::Forms::OpenFileDialog^  openModelDialog1;
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog;
	private: System::Windows::Forms::SaveFileDialog^  saveModelDialog;
	private: System::Windows::Forms::ToolStripMenuItem^  saveModelToolStripMenuItem;
	private: HKOGLPanel::HKOGLPanelControl^  hkoglPanelControl1;
	private: System::Windows::Forms::CheckBox^  checkBox1;
	private: System::Windows::Forms::CheckBox^  checkBox2;
	private: System::Windows::Forms::CheckBox^  checkBox3;
	private: System::Windows::Forms::CheckBox^  checkBox4;
	private: HKOGLPanel::HKOGLPanelControl^  hkoglPanelControl2;

	private: HKOGLPanel::HKOGLPanelControl^  hkoglPanelControl4;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Button^  button2;

	private: System::Windows::Forms::Button^  button4;
	private: System::Windows::Forms::ListBox^  listBox1;
	private: System::Windows::Forms::Button^  button5;
	private: System::Windows::Forms::Button^  button6;
	private: System::Windows::Forms::ListBox^  listBox2;

	private: System::Windows::Forms::Button^  button7;
	private: HKOGLPanel::HKOGLPanelControl^  hkoglPanelControl3;
	private: System::Windows::Forms::Button^  button3;


	protected:

	private:
		/// <summary>
		/// 設計工具所需的變數。
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// 此為設計工具支援所需的方法 - 請勿使用程式碼編輯器修改
		/// 這個方法的內容。
		/// </summary>
		void InitializeComponent(void)
		{
			HKOGLPanel::HKCOGLPanelCameraSetting^  hkcoglPanelCameraSetting1 = (gcnew HKOGLPanel::HKCOGLPanelCameraSetting());
			HKOGLPanel::HKCOGLPanelPixelFormat^  hkcoglPanelPixelFormat1 = (gcnew HKOGLPanel::HKCOGLPanelPixelFormat());
			HKOGLPanel::HKCOGLPanelCameraSetting^  hkcoglPanelCameraSetting2 = (gcnew HKOGLPanel::HKCOGLPanelCameraSetting());
			HKOGLPanel::HKCOGLPanelPixelFormat^  hkcoglPanelPixelFormat2 = (gcnew HKOGLPanel::HKCOGLPanelPixelFormat());
			HKOGLPanel::HKCOGLPanelCameraSetting^  hkcoglPanelCameraSetting3 = (gcnew HKOGLPanel::HKCOGLPanelCameraSetting());
			HKOGLPanel::HKCOGLPanelPixelFormat^  hkcoglPanelPixelFormat3 = (gcnew HKOGLPanel::HKCOGLPanelPixelFormat());
			HKOGLPanel::HKCOGLPanelCameraSetting^  hkcoglPanelCameraSetting4 = (gcnew HKOGLPanel::HKCOGLPanelCameraSetting());
			HKOGLPanel::HKCOGLPanelPixelFormat^  hkcoglPanelPixelFormat4 = (gcnew HKOGLPanel::HKCOGLPanelPixelFormat());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->loadModelToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->saveModelToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openModelDialog = (gcnew System::Windows::Forms::OpenFileDialog());
			this->openModelDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->openFileDialog = (gcnew System::Windows::Forms::OpenFileDialog());
			this->saveModelDialog = (gcnew System::Windows::Forms::SaveFileDialog());
			this->hkoglPanelControl1 = (gcnew HKOGLPanel::HKOGLPanelControl());
			this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox2 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox3 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox4 = (gcnew System::Windows::Forms::CheckBox());
			this->hkoglPanelControl2 = (gcnew HKOGLPanel::HKOGLPanelControl());
			this->hkoglPanelControl4 = (gcnew HKOGLPanel::HKOGLPanelControl());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->listBox1 = (gcnew System::Windows::Forms::ListBox());
			this->button5 = (gcnew System::Windows::Forms::Button());
			this->button6 = (gcnew System::Windows::Forms::Button());
			this->listBox2 = (gcnew System::Windows::Forms::ListBox());
			this->button7 = (gcnew System::Windows::Forms::Button());
			this->hkoglPanelControl3 = (gcnew HKOGLPanel::HKOGLPanelControl());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->menuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// menuStrip1
			// 
			this->menuStrip1->ImageScalingSize = System::Drawing::Size(24, 24);
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->fileToolStripMenuItem });
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Padding = System::Windows::Forms::Padding(9, 3, 0, 3);
			this->menuStrip1->Size = System::Drawing::Size(1340, 33);
			this->menuStrip1->TabIndex = 1;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// fileToolStripMenuItem
			// 
			this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->loadModelToolStripMenuItem,
					this->saveModelToolStripMenuItem
			});
			this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
			this->fileToolStripMenuItem->Size = System::Drawing::Size(51, 27);
			this->fileToolStripMenuItem->Text = L"File";
			// 
			// loadModelToolStripMenuItem
			// 
			this->loadModelToolStripMenuItem->Name = L"loadModelToolStripMenuItem";
			this->loadModelToolStripMenuItem->Size = System::Drawing::Size(192, 30);
			this->loadModelToolStripMenuItem->Text = L"Load Model";
			this->loadModelToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::loadModelToolStripMenuItem_Click);
			// 
			// saveModelToolStripMenuItem
			// 
			this->saveModelToolStripMenuItem->Name = L"saveModelToolStripMenuItem";
			this->saveModelToolStripMenuItem->Size = System::Drawing::Size(192, 30);
			this->saveModelToolStripMenuItem->Text = L"Save Model";
			this->saveModelToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::saveModelToolStripMenuItem_Click);
			// 
			// openModelDialog
			// 
			this->openModelDialog->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &MyForm::openModelDialog_FileOk);
			// 
			// openModelDialog1
			// 
			this->openModelDialog1->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &MyForm::openModelDialog1_FileOk);
			// 
			// openFileDialog
			// 
			this->openFileDialog->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &MyForm::openFileDialog_FileOk);
			// 
			// saveModelDialog
			// 
			this->saveModelDialog->DefaultExt = L"obj";
			this->saveModelDialog->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &MyForm::saveModelDialog_FileOk);
			// 
			// hkoglPanelControl1
			// 
			hkcoglPanelCameraSetting1->Far = 1000;
			hkcoglPanelCameraSetting1->Fov = 45;
			hkcoglPanelCameraSetting1->Near = -1000;
			hkcoglPanelCameraSetting1->Type = HKOGLPanel::HKCOGLPanelCameraSetting::CAMERATYPE::ORTHOGRAPHIC;
			this->hkoglPanelControl1->Camera_Setting = hkcoglPanelCameraSetting1;
			this->hkoglPanelControl1->Dock = System::Windows::Forms::DockStyle::Left;
			this->hkoglPanelControl1->Location = System::Drawing::Point(0, 33);
			this->hkoglPanelControl1->Margin = System::Windows::Forms::Padding(4);
			this->hkoglPanelControl1->Name = L"hkoglPanelControl1";
			hkcoglPanelPixelFormat1->Accumu_Buffer_Bits = HKOGLPanel::HKCOGLPanelPixelFormat::PIXELBITS::BITS_0;
			hkcoglPanelPixelFormat1->Alpha_Buffer_Bits = HKOGLPanel::HKCOGLPanelPixelFormat::PIXELBITS::BITS_0;
			hkcoglPanelPixelFormat1->Stencil_Buffer_Bits = HKOGLPanel::HKCOGLPanelPixelFormat::PIXELBITS::BITS_0;
			this->hkoglPanelControl1->Pixel_Format = hkcoglPanelPixelFormat1;
			this->hkoglPanelControl1->Size = System::Drawing::Size(620, 648);
			this->hkoglPanelControl1->TabIndex = 2;
			this->hkoglPanelControl1->Load += gcnew System::EventHandler(this, &MyForm::hkoglPanelControl1_Load);
			this->hkoglPanelControl1->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::hkoglPanelControl1_Paint);
			this->hkoglPanelControl1->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::hkoglPanelControl1_MouseDown);
			this->hkoglPanelControl1->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::hkoglPanelControl1_MouseMove);
			this->hkoglPanelControl1->MouseWheel += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::hkoglPanelControl1_MouseWheel);
			// 
			// checkBox1
			// 
			this->checkBox1->AutoSize = true;
			this->checkBox1->Location = System::Drawing::Point(84, 4);
			this->checkBox1->Name = L"checkBox1";
			this->checkBox1->Size = System::Drawing::Size(64, 22);
			this->checkBox1->TabIndex = 3;
			this->checkBox1->Text = L"face";
			this->checkBox1->UseVisualStyleBackColor = true;
			this->checkBox1->CheckedChanged += gcnew System::EventHandler(this, &MyForm::checkBox1_CheckedChanged);
			// 
			// checkBox2
			// 
			this->checkBox2->AutoSize = true;
			this->checkBox2->Location = System::Drawing::Point(154, 4);
			this->checkBox2->Name = L"checkBox2";
			this->checkBox2->Size = System::Drawing::Size(68, 22);
			this->checkBox2->TabIndex = 4;
			this->checkBox2->Text = L"point";
			this->checkBox2->UseVisualStyleBackColor = true;
			this->checkBox2->CheckedChanged += gcnew System::EventHandler(this, &MyForm::checkBox2_CheckedChanged);
			// 
			// checkBox3
			// 
			this->checkBox3->AutoSize = true;
			this->checkBox3->Location = System::Drawing::Point(228, 4);
			this->checkBox3->Name = L"checkBox3";
			this->checkBox3->Size = System::Drawing::Size(122, 22);
			this->checkBox3->TabIndex = 5;
			this->checkBox3->Text = L"pick_onering";
			this->checkBox3->UseVisualStyleBackColor = true;
			this->checkBox3->CheckedChanged += gcnew System::EventHandler(this, &MyForm::checkBox3_CheckedChanged);
			// 
			// checkBox4
			// 
			this->checkBox4->AutoSize = true;
			this->checkBox4->Location = System::Drawing::Point(356, 4);
			this->checkBox4->Name = L"checkBox4";
			this->checkBox4->Size = System::Drawing::Size(101, 22);
			this->checkBox4->TabIndex = 6;
			this->checkBox4->Text = L"pick_face";
			this->checkBox4->UseVisualStyleBackColor = true;
			this->checkBox4->CheckedChanged += gcnew System::EventHandler(this, &MyForm::checkBox4_CheckedChanged);
			// 
			// hkoglPanelControl2
			// 
			hkcoglPanelCameraSetting2->Far = 1000;
			hkcoglPanelCameraSetting2->Fov = 45;
			hkcoglPanelCameraSetting2->Near = -1000;
			hkcoglPanelCameraSetting2->Type = HKOGLPanel::HKCOGLPanelCameraSetting::CAMERATYPE::ORTHOGRAPHIC;
			this->hkoglPanelControl2->Camera_Setting = hkcoglPanelCameraSetting2;
			this->hkoglPanelControl2->Location = System::Drawing::Point(627, 284);
			this->hkoglPanelControl2->Name = L"hkoglPanelControl2";
			hkcoglPanelPixelFormat2->Accumu_Buffer_Bits = HKOGLPanel::HKCOGLPanelPixelFormat::PIXELBITS::BITS_0;
			hkcoglPanelPixelFormat2->Alpha_Buffer_Bits = HKOGLPanel::HKCOGLPanelPixelFormat::PIXELBITS::BITS_0;
			hkcoglPanelPixelFormat2->Stencil_Buffer_Bits = HKOGLPanel::HKCOGLPanelPixelFormat::PIXELBITS::BITS_0;
			this->hkoglPanelControl2->Pixel_Format = hkcoglPanelPixelFormat2;
			this->hkoglPanelControl2->Size = System::Drawing::Size(261, 232);
			this->hkoglPanelControl2->TabIndex = 7;
			this->hkoglPanelControl2->Load += gcnew System::EventHandler(this, &MyForm::hkoglPanelControl2_Load);
			this->hkoglPanelControl2->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::hkoglPanelControl2_Paint);
			this->hkoglPanelControl2->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::hkoglPanelControl2_MouseDown);
			// 
			// hkoglPanelControl4
			// 
			hkcoglPanelCameraSetting3->Far = 1000;
			hkcoglPanelCameraSetting3->Fov = 45;
			hkcoglPanelCameraSetting3->Near = -1000;
			hkcoglPanelCameraSetting3->Type = HKOGLPanel::HKCOGLPanelCameraSetting::CAMERATYPE::ORTHOGRAPHIC;
			this->hkoglPanelControl4->Camera_Setting = hkcoglPanelCameraSetting3;
			this->hkoglPanelControl4->Location = System::Drawing::Point(627, 118);
			this->hkoglPanelControl4->Name = L"hkoglPanelControl4";
			hkcoglPanelPixelFormat3->Accumu_Buffer_Bits = HKOGLPanel::HKCOGLPanelPixelFormat::PIXELBITS::BITS_0;
			hkcoglPanelPixelFormat3->Alpha_Buffer_Bits = HKOGLPanel::HKCOGLPanelPixelFormat::PIXELBITS::BITS_0;
			hkcoglPanelPixelFormat3->Stencil_Buffer_Bits = HKOGLPanel::HKCOGLPanelPixelFormat::PIXELBITS::BITS_0;
			this->hkoglPanelControl4->Pixel_Format = hkcoglPanelPixelFormat3;
			this->hkoglPanelControl4->Size = System::Drawing::Size(156, 147);
			this->hkoglPanelControl4->TabIndex = 9;
			this->hkoglPanelControl4->Load += gcnew System::EventHandler(this, &MyForm::hkoglPanelControl4_Load);
			this->hkoglPanelControl4->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::hkoglPanelControl4_Paint);
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(463, 0);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(82, 30);
			this->button1->TabIndex = 10;
			this->button1->Text = L"turn 2d";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(551, 1);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(84, 29);
			this->button2->TabIndex = 11;
			this->button2->Text = L"貼圖";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// button4
			// 
			this->button4->Location = System::Drawing::Point(641, 1);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(132, 29);
			this->button4->TabIndex = 13;
			this->button4->Text = L"save copymesh";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &MyForm::button4_Click);
			// 
			// listBox1
			// 
			this->listBox1->FormattingEnabled = true;
			this->listBox1->ItemHeight = 18;
			this->listBox1->Location = System::Drawing::Point(789, 36);
			this->listBox1->Name = L"listBox1";
			this->listBox1->Size = System::Drawing::Size(528, 112);
			this->listBox1->TabIndex = 14;
			this->listBox1->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::listBox1_SelectedIndexChanged);
			// 
			// button5
			// 
			this->button5->Location = System::Drawing::Point(1209, 2);
			this->button5->Name = L"button5";
			this->button5->Size = System::Drawing::Size(88, 28);
			this->button5->TabIndex = 15;
			this->button5->Text = L"clear";
			this->button5->UseVisualStyleBackColor = true;
			this->button5->Click += gcnew System::EventHandler(this, &MyForm::button5_Click);
			// 
			// button6
			// 
			this->button6->Location = System::Drawing::Point(894, 1);
			this->button6->Name = L"button6";
			this->button6->Size = System::Drawing::Size(76, 35);
			this->button6->TabIndex = 16;
			this->button6->Text = L"load obj";
			this->button6->UseVisualStyleBackColor = true;
			this->button6->Click += gcnew System::EventHandler(this, &MyForm::button6_Click);
			// 
			// listBox2
			// 
			this->listBox2->FormattingEnabled = true;
			this->listBox2->ItemHeight = 18;
			this->listBox2->Location = System::Drawing::Point(789, 153);
			this->listBox2->Name = L"listBox2";
			this->listBox2->Size = System::Drawing::Size(528, 112);
			this->listBox2->TabIndex = 17;
			this->listBox2->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::listBox2_SelectedIndexChanged);
			// 
			// button7
			// 
			this->button7->Location = System::Drawing::Point(991, 1);
			this->button7->Name = L"button7";
			this->button7->Size = System::Drawing::Size(168, 29);
			this->button7->TabIndex = 19;
			this->button7->Text = L"load texture";
			this->button7->UseVisualStyleBackColor = true;
			this->button7->Click += gcnew System::EventHandler(this, &MyForm::button7_Click);
			// 
			// hkoglPanelControl3
			// 
			hkcoglPanelCameraSetting4->Far = 1000;
			hkcoglPanelCameraSetting4->Fov = 45;
			hkcoglPanelCameraSetting4->Near = -1000;
			hkcoglPanelCameraSetting4->Type = HKOGLPanel::HKCOGLPanelCameraSetting::CAMERATYPE::ORTHOGRAPHIC;
			this->hkoglPanelControl3->Camera_Setting = hkcoglPanelCameraSetting4;
			this->hkoglPanelControl3->Location = System::Drawing::Point(898, 271);
			this->hkoglPanelControl3->Name = L"hkoglPanelControl3";
			hkcoglPanelPixelFormat4->Accumu_Buffer_Bits = HKOGLPanel::HKCOGLPanelPixelFormat::PIXELBITS::BITS_0;
			hkcoglPanelPixelFormat4->Alpha_Buffer_Bits = HKOGLPanel::HKCOGLPanelPixelFormat::PIXELBITS::BITS_0;
			hkcoglPanelPixelFormat4->Stencil_Buffer_Bits = HKOGLPanel::HKCOGLPanelPixelFormat::PIXELBITS::BITS_0;
			this->hkoglPanelControl3->Pixel_Format = hkcoglPanelPixelFormat4;
			this->hkoglPanelControl3->Size = System::Drawing::Size(442, 410);
			this->hkoglPanelControl3->TabIndex = 20;
			this->hkoglPanelControl3->Load += gcnew System::EventHandler(this, &MyForm::hkoglPanelControl3_Load);
			this->hkoglPanelControl3->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::hkoglPanelControl3_Paint);
			this->hkoglPanelControl3->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::hkoglPanelControl3_MouseDown);
			this->hkoglPanelControl3->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::hkoglPanelControl3_MouseMove);
			// 
			// button3
			// 
			this->button3->Font = (gcnew System::Drawing::Font(L"新細明體", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->button3->Location = System::Drawing::Point(633, 522);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(229, 142);
			this->button3->TabIndex = 21;
			this->button3->Text = L"bind texture";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &MyForm::button3_Click_1);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 18);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1340, 681);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->hkoglPanelControl3);
			this->Controls->Add(this->button7);
			this->Controls->Add(this->listBox2);
			this->Controls->Add(this->button6);
			this->Controls->Add(this->button5);
			this->Controls->Add(this->listBox1);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->hkoglPanelControl4);
			this->Controls->Add(this->hkoglPanelControl2);
			this->Controls->Add(this->checkBox4);
			this->Controls->Add(this->checkBox3);
			this->Controls->Add(this->checkBox2);
			this->Controls->Add(this->checkBox1);
			this->Controls->Add(this->hkoglPanelControl1);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Margin = System::Windows::Forms::Padding(4);
			this->Name = L"MyForm";
			this->Text = L"OpenMesh_EX";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::MyForm_MouseClick);
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
private: System::Void hkoglPanelControl1_Load(System::Object^  sender, System::EventArgs^  e)
{
	glDepthFunc(GL_LEQUAL);
}
private: System::Void hkoglPanelControl1_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e)
{
	glEnable(GL_COLOR_MATERIAL);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	point center;
	center[0] = 0.0;
	center[1] = 0.0;
	center[2] = 0.0;
	camera.setupGL(xf * center, 1.0);


	glPushMatrix();
	glMatrixMode(GL_MODELVIEW);
	glMultMatrixd((double *)xf);
	if (mesh != NULL)
		mesh->Render_SolidWireframe();
	//hkoglPanelControl1->Invalidate();
	
	glColor3f(255, 0, 0);
	glPointSize(5);
	glBegin(GL_POINTS);
	glVertex3f(position[0], position[1], position[2]);
	glEnd();
	
	
	
	if (select_fh.is_valid())
	{
		//glDisable(GL_DEPTH_TEST);
		glColor3f(0, 0, 255);
		glBegin(GL_TRIANGLES);
		for (OMT::FVIter fv_it = mesh->fv_iter(select_fh); fv_it; ++fv_it) 
			 glVertex3dv( mesh->point(fv_it.handle()).data());
		glEnd();
	}

	if (select_vh.is_valid())
	{
		//glDisable(GL_DEPTH_TEST);
		glColor3f(0, 255, 0);
		glPointSize(20);
		glBegin(GL_POINTS);
		glVertex3dv(mesh->point(select_vh).data());	
		glEnd();
	}

	if (select_fh_v.size() >= 1)
	{
		if (select_fh_v[0].is_valid())
		{
			//glDisable(GL_DEPTH_TEST);
			glColor3f(0, 0, 255);
			glBegin(GL_TRIANGLES);
			for (int i = 0; select_fh_v.size()>i; i++)
			{
				for (OMT::FVIter fv_it = mesh->fv_iter(select_fh_v[i]); fv_it; ++fv_it)
					glVertex3dv(mesh->point(fv_it.handle()).data());
			}
			glEnd();
		}
	}
	
	
	if (select_rfh_v.size() >= 1)
	{
		if (select_rfh_v[0].is_valid())
		{
			//glDisable(GL_DEPTH_TEST);
			glColor3f(0, 0, 255);
			glBegin(GL_TRIANGLES);
			for (int i = 0; select_rfh_v.size()>i; i++)
			{
				for (OMT::FVIter fv_it = mesh->fv_iter(select_rfh_v[i]); fv_it; ++fv_it)
					glVertex3dv(mesh->point(fv_it.handle()).data());
			}
			glEnd();
		}
		

	}
	

	if (copymesh != NULL)
	{
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		for (OMT::FIter f_it = copymesh->faces_begin(); f_it != copymesh->faces_end(); f_it++)
		{
			OMT::VertexHandle temp_copy_vhA;
			OMT::VertexHandle  temp_copy_vhB;
			OMT::VertexHandle  temp_copy_vhC;
			int A = 0, B = 0, C = 0;
			for (OMT::FVIter fv_it = copymesh->fv_iter(f_it); fv_it; fv_it++)
			{
				if (A == 0)
				{
					temp_copy_vhA = fv_it;
					A = 1;
				}
				else if (A == 1 && B == 0)
				{
					temp_copy_vhB = fv_it;
					B = 1;
				}
				else if (A == 1 && B == 1 && C == 0)
				{
					temp_copy_vhC = fv_it;
					C = 1;
				}
			}
			OMT::Point temp_copyA = copymesh->point(temp_copy_vhA);
			OMT::Point temp_copyB = copymesh->point(temp_copy_vhB);
			OMT::Point temp_copyC = copymesh->point(temp_copy_vhC);
			OMT::Point temp_2dA = copymesh->property(copymesh->bind_2d_to_3d, temp_copy_vhA);
			OMT::Point temp_2dB = copymesh->property(copymesh->bind_2d_to_3d, temp_copy_vhB);
			OMT::Point temp_2dC = copymesh->property(copymesh->bind_2d_to_3d, temp_copy_vhC);
			

			glPushMatrix();
			glBindTexture(GL_TEXTURE_2D, hair1);
			glBegin(GL_TRIANGLES);
			glTexCoord2d(temp_2dA[0], temp_2dA[1]); glVertex3d(temp_copyA[0], temp_copyA[1], temp_copyA[2]);
			glTexCoord2d(temp_2dB[0], temp_2dB[1]); glVertex3d(temp_copyB[0], temp_copyB[1], temp_copyB[2]);
			glTexCoord2d(temp_2dC[0], temp_2dC[1]); glVertex3d(temp_copyC[0], temp_copyC[1], temp_copyC[2]);
			glEnd();
			glPopMatrix();
		}
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_BLEND);

	}

	if (temp_mesh[0] != NULL)
	{


	}

	glPopMatrix();
	
	
	
	
		
	
	
}

private: System::Void hkoglPanelControl1_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
{
	if (e->Button == System::Windows::Forms::MouseButtons::Left ||
		e->Button == System::Windows::Forms::MouseButtons::Middle)
	{
		point center;
		Mouse_State = Mouse::NONE;
		center[0] = 0.0;
		center[1] = 0.0;
		center[2] = 0.0;
		camera.mouse(e->X, e->Y, Mouse_State,
			xf * center,
			1.0, xf);
		mouse_x = e->X;
		mouse_y = e->Y;

		

		glEnable(GL_DEPTH_TEST);
		glPushMatrix();
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glMultMatrixd((double *)xf);
		camera.read_depth(mouse_x, (hkoglPanelControl1->Height - mouse_y), position);
		glPopMatrix();
		
	}

	if (e->Button == System::Windows::Forms::MouseButtons::Left)
	{
		if (mesh != NULL)
		{
		
			if (face_confirm == 1)
			{
				select_fh = mesh->findface((double)position[0], (double)position[1], (double)position[2]);
			}
			if (point_confirm == 1)
			{
				select_vh = mesh->findpoint(position[0], position[1], position[2]);
			}
			if (pick_face_confirm == 1)
			{	
				
				select_fh_v = mesh->mouse_pick_face((double)position[0], (double)position[1], (double)position[2]);	

				//copy 3d mesh to new mesh
				mid_vh = mesh->return_middle((double)position[0], (double)position[1], (double)position[2]);
				std::vector<OMT::VertexHandle> tempcopyvh;
				
				//std::cout << select_fh_v.back().idx() << std::endl;
				if (first_copy_count != 1)
				{
					copymesh = new Tri_Mesh;
					mesh_2d = new Tri_Mesh;
					//copymesh->add_property(copy_point_id);
					copyvh.clear();
					copyvh = mesh->mouse_pick_face_vh((double)position[0], (double)position[1], (double)position[2]);
					const_copyvh.clear();
					
					if (!copyvh.empty())
					{
						tempcopyvh.clear();
						const_copyvh.push_back(copymesh->add_vertex(mesh->point(copyvh[0])));
						const_copyvh.push_back(copymesh->add_vertex(mesh->point(copyvh[1])));
						const_copyvh.push_back(copymesh->add_vertex(mesh->point(copyvh[2])));
						tempcopyvh.push_back(const_copyvh[0]);
						tempcopyvh.push_back(const_copyvh[1]);
						tempcopyvh.push_back(const_copyvh[2]);
						copymesh->property(copymesh->copy_point_id, const_copyvh[0]) = 1;
						copymesh->property(copymesh->copy_point_id, const_copyvh[1]) = 2;
						copymesh->property(copymesh->copy_point_id, const_copyvh[2]) = 3;
						face_order.push_back(1);
						face_order.push_back(2);
						face_order.push_back(3);
						copyfh.push_back(copymesh->add_face(tempcopyvh));
						first_copy_count = 1;
					}
				}
				else
				{
					if (select_fh_v.back().is_valid() && !copyvh.empty())
					{
						int is_new = 1;
						three_vh.clear();
						tempcopyvh.clear();
						copyvh = mesh->mouse_pick_face_vh((double)position[0], (double)position[1], (double)position[2]);
						three_vh = mesh->copy_point_repeat(copyvh, select_fh_v.back());
						for (int n = 0; n < 3; n++)
						{
							is_new = 1;
							for (int i = 0; i <const_copyvh.size(); i++)
							{							
								if (mesh->point(three_vh[n])[0] == copymesh->point(const_copyvh[i])[0] && mesh->point(three_vh[n])[1] == copymesh->point(const_copyvh[i])[1] && mesh->point(three_vh[n])[2] == copymesh->point(const_copyvh[i])[2])
								{
									tempcopyvh.push_back(const_copyvh[i]);
									face_order.push_back(copymesh->property(copymesh->copy_point_id, const_copyvh[i]));
									is_new = 0;
									break;
								}
							}
							if (is_new == 1)
							{
								const_copyvh.push_back(copymesh->add_vertex(mesh->point(three_vh[n])));
								copymesh->property(copymesh->copy_point_id, const_copyvh[const_copyvh.size() - 1]) = const_copyvh.size();
								face_order.push_back(copymesh->property(copymesh->copy_point_id, const_copyvh[const_copyvh.size() - 1]));
								tempcopyvh.push_back(const_copyvh.back());
							}
						}
						copyfh.push_back(copymesh->add_face(tempcopyvh));
					}					
				}
				//copy 3d mesh to new mesh end
				std::cout << "copy size   "<<const_copyvh.size() << std::endl;

			}//pickface end




			if (mouse_pick_roundface_confirm == 1)
			{
				select_rfh_v = mesh->mouse_pick_roundface((double)position[0], (double)position[1], (double)position[2]);
			}//pick round face end
			
		}
	}
	hkoglPanelControl1->Invalidate();
	hkoglPanelControl2->Invalidate();
	hkoglPanelControl3->Invalidate();
	hkoglPanelControl4->Invalidate();
}
private: System::Void hkoglPanelControl1_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
{
	if (e->Button == System::Windows::Forms::MouseButtons::Left)
	{
		point center;
		Mouse_State = Mouse::ROTATE;
		center[0] = 0.0;
		center[1] = 0.0;
		center[2] = 0.0;
		camera.mouse(e->X, e->Y, Mouse_State,
			xf * center,
			1.0, xf);
		hkoglPanelControl1->Invalidate();
		hkoglPanelControl3->Invalidate();
		mouse_x = e->X;
		mouse_y = e->Y;

	}

	if (e->Button == System::Windows::Forms::MouseButtons::Middle)
	{
		point center;
		Mouse_State = Mouse::MOVEXY;
		center[0] = 0.0;
		center[1] = 0.0;
		center[2] = 0.0;
		camera.mouse(e->X, e->Y, Mouse_State,
			xf * center,
			1.0, xf);
		hkoglPanelControl1->Invalidate();
		hkoglPanelControl3->Invalidate();
		mouse_x = e->X;
		mouse_y = e->Y;
	}
}
private: System::Void hkoglPanelControl1_MouseWheel(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
{
	if (e->Delta < 0)
	{
		point center;
		Mouse_State = Mouse::WHEELDOWN;
		center[0] = 0.0;
		center[1] = 0.0;
		center[2] = 0.0;
		camera.mouse(e->X, e->Y, Mouse_State,
			xf * center,
			1.0, xf);
		hkoglPanelControl1->Invalidate();
		hkoglPanelControl3->Invalidate();
	}
	else
	{
		point center;
		Mouse_State = Mouse::WHEELUP;
		center[0] = 0.0;
		center[1] = 0.0;
		center[2] = 0.0;
		camera.mouse(e->X, e->Y, Mouse_State,
			xf * center,
			1.0, xf);
		hkoglPanelControl1->Invalidate();
		hkoglPanelControl3->Invalidate();
	}
}
private: System::Void loadModelToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
{
	openModelDialog->Filter = "Model(*.obj)|*obj";
	openModelDialog->Multiselect = false;
	openModelDialog->ShowDialog();
}
private: System::Void openModelDialog_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e)
{
	std::string filename;
	MarshalString(openModelDialog->FileName, filename);

	if (mesh != NULL)
		delete mesh;

	mesh = new Tri_Mesh;

	if (ReadFile(filename, mesh))
		std::cout << filename << std::endl;

	hkoglPanelControl1->Invalidate();
	hkoglPanelControl3->Invalidate();
}
private: System::Void openModelDialog1_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e)
{
	std::string filename[100];

	for (int i = 0; i<openModelDialog1->FileNames->Length; i++)
 {
	 MarshalString(openModelDialog1->FileNames[i], filename[i]);
	 std::cout << i << " = " << filename[i] << std::endl;
 }
 for (int i = 0; i<openModelDialog1->FileNames->Length; i++)
 {

	 temp_mesh[meshnum] = new Tri_Mesh;
	 if (ReadFile(filename[i], temp_mesh[meshnum]))
		 std::cout << "Loaded mesh:" << filename[i] << std::endl;
	 loadedmeshnum++;
	 listBox1->Items->Add((System::Object ^)openModelDialog1->FileNames[i]);
	 meshnum++;
 }
}
private: System::Void openFileDialog_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e)
{
	std::string filename[100];

	for (int i = 0; i<openFileDialog->FileNames->Length; i++)
	{
		MarshalString(openFileDialog->FileNames[i], filename[i]);
		//std::cout << i << " = " << filename[i] << std::endl;
	}


	for (int i = 0; i<openFileDialog->FileNames->Length; i++)
	{
		texture[texturenum] = NULL;
		hkoglPanelControl3->Refresh();
		texture[texturenum] = TextureApp::GenTexture((char *)filename[i].c_str());
		donetexture[texturenum] = (char *)filename[i].c_str();
		//TextureApp::AddTexture(filename[i], texturenum);
		std::cout << "Loaded Texture:" << filename[i] << std::endl;
		listBox2->Items->Add((System::Object ^)openFileDialog->FileNames[i]);

		//loadedtexturenum++;
		texturenum++;
		hkoglPanelControl1->Invalidate();
		hkoglPanelControl3->Invalidate();
	}
}
private: System::Void saveModelToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
{
	saveModelDialog->Filter = "Model(*.obj)|*obj";
	saveModelDialog->ShowDialog();
}
private: System::Void saveModelDialog_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e)
{
	std::string filename;
	MarshalString(saveModelDialog->FileName, filename);

	if (SaveFile(filename, mesh))
		std::cout << filename << std::endl;
}

private: System::Void checkBox1_CheckedChanged(System::Object^  sender, System::EventArgs^  e) 
{
	if (checkBox1->Checked)
		face_confirm = 1;
	else
		face_confirm = 0;
}
private: System::Void checkBox2_CheckedChanged(System::Object^  sender, System::EventArgs^  e) 
{
	if (checkBox2->Checked)
		point_confirm = 1;
	else
		point_confirm = 0;
}
private: System::Void checkBox3_CheckedChanged(System::Object^  sender, System::EventArgs^  e) 
{
	if (checkBox3->Checked)
		mouse_pick_roundface_confirm = 1;
	else
		mouse_pick_roundface_confirm = 0;
}
private: System::Void checkBox4_CheckedChanged(System::Object^  sender, System::EventArgs^  e) 
{
	if (checkBox4->Checked)
		pick_face_confirm = 1;
	else
		pick_face_confirm = 0;
}
private: System::Void MyForm_Load(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void hkoglPanelControl2_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e)
{
	glDisable(GL_COLOR_MATERIAL);
	glDisable(GL_LIGHTING);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glOrtho(0, 1, 0, 1, -10, 10);



	
	if (!fh_v.empty())
	{


		glLineWidth(1.0);
		glColor3f(1.0, 0.0, 0.0);
		glBegin(GL_LINES);
		for (OMT::EIter e_it= mesh_2d->edges_begin() ; e_it != mesh_2d->edges_end(); ++e_it)
		{
			OMT::HEHandle _hedge = mesh_2d->halfedge_handle(e_it.handle(), 1);

			OMT::Point curVertex = mesh_2d->point(mesh_2d->from_vertex_handle(_hedge));
			glVertex3dv(curVertex.data());

			curVertex = mesh_2d->point(mesh_2d->to_vertex_handle(_hedge));
			glVertex3dv(curVertex.data());
			std::cout << "mesh_2d" << std::endl;
		}
		glEnd();
		
	}
	
	
}
private: System::Void hkoglPanelControl2_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) 
{

}
private: System::Void hkoglPanelControl2_Load(System::Object^  sender, System::EventArgs^  e) 
{

}


private: System::Void hkoglPanelControl4_Load(System::Object^  sender, System::EventArgs^  e) 
{

}
private: System::Void hkoglPanelControl4_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) 
{
	glDisable(GL_COLOR_MATERIAL);
	glDisable(GL_LIGHTING);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glOrtho(-0.5, 0.5, -0.5, 0.5, -5, 5);

	if (copymesh != NULL)
	{
		glLineWidth(1.0);
		glColor3f(0.0, 0.0, 0.0);
		glBegin(GL_LINES);
		for (OMT::EIter e_it = copymesh->edges_begin(); e_it != copymesh->edges_end(); ++e_it)
		{
			OMT::HEHandle _hedge = copymesh->halfedge_handle(e_it.handle(), 1);

			OMT::Point curVertex = copymesh->point(copymesh->from_vertex_handle(_hedge));
			glVertex3dv(curVertex.data());

			curVertex = copymesh->point(copymesh->to_vertex_handle(_hedge));
			glVertex3dv(curVertex.data());
		}
		glEnd();
		
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		for (OMT::FIter f_it = copymesh->faces_begin(); f_it != copymesh->faces_end(); f_it++)
		{
			OMT::VertexHandle temp_copy_vhA;
			OMT::VertexHandle  temp_copy_vhB;
			OMT::VertexHandle  temp_copy_vhC;
			int A = 0, B = 0, C = 0;
			for (OMT::FVIter fv_it = copymesh->fv_iter(f_it); fv_it; fv_it++)
			{
				if (A == 0)
				{
					temp_copy_vhA = fv_it;
					A = 1;
				}
				else if (A == 1 && B == 0)
				{
					temp_copy_vhB = fv_it;
					B = 1;
				}
				else if (A == 1 && B == 1 && C == 0)
				{
					temp_copy_vhC = fv_it;
					C = 1;
				}
			}
			OMT::Point temp_copyA = copymesh->point(temp_copy_vhA);
			OMT::Point temp_copyB = copymesh->point(temp_copy_vhB);
			OMT::Point temp_copyC = copymesh->point(temp_copy_vhC);
			OMT::Point temp_2dA = copymesh->property(copymesh->bind_2d_to_3d, temp_copy_vhA);
			OMT::Point temp_2dB = copymesh->property(copymesh->bind_2d_to_3d, temp_copy_vhB);
			OMT::Point temp_2dC = copymesh->property(copymesh->bind_2d_to_3d, temp_copy_vhC);
			

			glPushMatrix();
			glBindTexture(GL_TEXTURE_2D, hair4);
			glBegin(GL_TRIANGLES);
			glTexCoord2d(temp_2dA[0], temp_2dA[1]); glVertex3d(temp_copyA[0], temp_copyA[1], temp_copyA[2]);
			glTexCoord2d(temp_2dB[0], temp_2dB[1]); glVertex3d(temp_copyB[0], temp_copyB[1], temp_copyB[2]);
			glTexCoord2d(temp_2dC[0], temp_2dC[1]); glVertex3d(temp_copyC[0], temp_copyC[1], temp_copyC[2]);
			glEnd();
			glPopMatrix();
		}
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_BLEND);
	}
	
}
private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) 
{
	for (OMT::VIter v_itr = copymesh->vertices_begin(); v_itr != copymesh->vertices_end(); ++v_itr)
	{
		std::cout << "all id   1111   " << copymesh->property(copymesh->copy_point_id, v_itr.handle()) << std::endl;
	}


	//calculate proportion

	double surround = 0;
	//outside_point.clear();

	int outsidepoint_count = 0;
	is_first_point = 0;
	length.clear();
	std::vector<int>  order;
	std::vector<OMT::VertexHandle> outsidevh;
	int tempid;
	OMT::HEHandle _hedge;
	OMT::HEHandle first_hedge;
	for (OMT::EIter e_it = copymesh->edges_begin(); e_it != copymesh->edges_end(); ++e_it)
	{	
		first_hedge = copymesh->halfedge_handle(e_it.handle(), 1);		
		if (copymesh->is_boundary(first_hedge))
		{
			_hedge = first_hedge;
			break;
		}
		
	}
	while (1)
	{
		OMT::Point curVertex_from = copymesh->point(copymesh->from_vertex_handle(_hedge));
		OMT::Point curVertex_to = copymesh->point(copymesh->to_vertex_handle(_hedge));

		if (is_first_point != 1)
		{
			tempid = copymesh->property(copymesh->copy_point_id, copymesh->from_vertex_handle(_hedge));
			order.push_back(tempid);
			std::cout << "  order  " << order[0] << std::endl;

			outsidevh.clear();
			
			outsidevh.push_back(copymesh->from_vertex_handle(_hedge));

			//std::cout << copymesh->property(copymesh->copy_point_id, copymesh->from_vertex_handle(_hedge)) << "   nbvggggggg" << std::endl;

			outsidepoint_count++;
			copymesh->property(copymesh->point_num, copymesh->from_vertex_handle(_hedge)) = outsidepoint_count;
			//std::cout << outsidepoint_count << "  outsidepoint_count" << std::endl;
			std::cout << copymesh->property(copymesh->point_num, copymesh->from_vertex_handle(_hedge)) << "  1point_num" << std::endl;

			//std::cout << copymesh->property(copymesh->copy_point_id, copymesh->from_vertex_handle(_hedge)) << "   2nbvggggggg" << std::endl;


			is_first_point = 1;
			outside_point.push_back(curVertex_from);
			lengthAB = sqrt(pow(curVertex_from[0] - curVertex_to[0], 2) + pow(curVertex_from[1] - curVertex_to[1], 2) + pow(curVertex_from[2] - curVertex_to[2], 2));
			length.push_back(lengthAB);
			surround += lengthAB;
		}
		else if (is_first_point == 1)
		{
			
			tempid = copymesh->property(copymesh->copy_point_id, copymesh->from_vertex_handle(_hedge));
			order.push_back(tempid);
			std::cout << "  order  " << order[order.size() - 1] << std::endl;

			outsidevh.push_back(copymesh->from_vertex_handle(_hedge));
			//std::cout << copymesh->property(copymesh->copy_point_id, outsidevh[outsidevh.size() - 1]) << "   dsadasdadsd" << std::endl;


			outside_point.push_back(curVertex_from);
			outsidepoint_count++;
			//std::cout << outsidepoint_count << "  1outsidepoint_count" << std::endl;
			copymesh->property(copymesh->point_num, copymesh->from_vertex_handle(_hedge)) = outsidepoint_count;
			//std::cout << outsidepoint_count << "  outsidepoint_count" << std::endl;
			//std::cout << copymesh->property(copymesh->point_num, copymesh->from_vertex_handle(_hedge)) << "  1point_num" << std::endl;

			lengthAB = sqrt(pow(curVertex_from[0] - curVertex_to[0], 2) + pow(curVertex_from[1] - curVertex_to[1], 2) + pow(curVertex_from[2] - curVertex_to[2], 2));
			length.push_back(lengthAB);
			surround += lengthAB;
		}
		for (int i = 0; i < outsidevh.size(); i++)
		{
			std::cout << "outside id  " << copymesh->property(copymesh->copy_point_id, outsidevh[i]) << std::endl;
		}
		_hedge = copymesh->next_halfedge_handle(_hedge);
		if (_hedge == first_hedge)
		{
			break;
		}
	}
	for (int i = 0; i < outsidevh.size(); i++)
	{
		std::cout << copymesh->property(copymesh->point_num, outsidevh[i]) << "  point_num" << std::endl;
	}
	
	for (OMT::VIter v_itr = copymesh->vertices_begin(); v_itr != copymesh->vertices_end(); ++v_itr)
	{
		std::cout << "all id   22222   " << copymesh->property(copymesh->copy_point_id, v_itr.handle()) << std::endl;
	}

	for (int i = 0; i < length.size(); i++)
	{
		proportion.push_back(4 * length[i] / surround);
		std::cout << "  length" << 4 * length[i] / surround << std::endl;
	}

	//calculate proportion
	std::cout << "outside point size  " << outside_point.size() << std::endl;
	//add ouside point to 2d
	double current_length = 0;

	vh_v.push_back(mesh_2d->add_vertex(OMT::Point(0, 0, 0)));
	mesh_2d->property(mesh_2d->point_num_2d, vh_v[0]) = 1;
	mesh_2d->property(mesh_2d->point_2d_id, vh_v[0]) = order[0];

	for (int i = 0; i < proportion.size() - 1; i++)
	{
		if (current_length + proportion[i] <= 1)
		{
			vh_v.push_back(mesh_2d->add_vertex(OMT::Point(current_length+proportion[i], 0, 0)));
			mesh_2d->property(mesh_2d->point_2d_id, vh_v[i + 1]) = order[i+1];
			mesh_2d->property(mesh_2d->point_num_2d, vh_v[i + 1]) = i + 2;
			current_length += proportion[i];
		}
		else if (current_length + proportion[i] > 1 && proportion[i] + current_length <= 2)
		{
			vh_v.push_back(mesh_2d->add_vertex(OMT::Point(1, current_length + proportion[i] - 1, 0)));
			mesh_2d->property(mesh_2d->point_2d_id, vh_v[i + 1]) = order[i + 1];
			mesh_2d->property(mesh_2d->point_num_2d, vh_v[i + 1]) = i + 2;
			current_length += proportion[i];			
		}
		else if (current_length + proportion[i] > 2 && proportion[i] + current_length <= 3)
		{
			vh_v.push_back(mesh_2d->add_vertex(OMT::Point(3 - current_length - proportion[i], 1, 0)));
			mesh_2d->property(mesh_2d->point_2d_id, vh_v[i + 1]) = order[i + 1];
			mesh_2d->property(mesh_2d->point_num_2d, vh_v[i + 1]) = i + 2;
			current_length += proportion[i];		
		}
		else
		{
			vh_v.push_back(mesh_2d->add_vertex(OMT::Point(0, 4 - current_length - proportion[i], 0)));
			mesh_2d->property(mesh_2d->point_2d_id, vh_v[i + 1]) = order[i + 1];
			mesh_2d->property(mesh_2d->point_num_2d, vh_v[i + 1]) = i + 2;
			current_length += proportion[i];	
		}
	}
	//add ouside point to 2d

	for (int i = 0; i < outsidevh.size(); i++)
	{
		std::cout << "2d outside id  " << mesh_2d->property(mesh_2d->point_2d_id, vh_v[i]) << std::endl;
	}

	std::vector<OMT::VertexHandle> inside_point;
	int inside_point_num = outsidepoint_count;
	//determine inside point
	for (OMT::VIter v_itr = copymesh->vertices_begin(); v_itr != copymesh->vertices_end(); ++v_itr)
	{
		std::cout << "all id   " << copymesh->property(copymesh->copy_point_id, v_itr.handle()) << std::endl;
		OMT::Point check_point = copymesh->point(v_itr.handle());
		int inside_check = 1;
		for (int i = 0; i < outsidevh.size(); i++)
		{
			if (v_itr.handle() == outsidevh[i])
			{
				inside_check = 0;
				break;
			}
		}
		if (inside_check == 1)
		{
			inside_point_num++;
			//copymesh->property(copymesh->point_num, v_itr.handle()) = inside_point_num;
			inside_point.push_back(v_itr.handle());
			//copymesh->property(copy_point_id, inside_point[inside_point.size()-1]) = copymesh->property(copy_point_id, v_itr.handle());
			std::cout << "inside id" << copymesh->property(copymesh->copy_point_id, v_itr.handle()) << std::endl;
		}
	}
	std::cout << "inside point size   " << inside_point.size() << std::endl;
	//determine inside point


	//calculate inside point position
	SparseMatrix<double> Ax(inside_point.size(), inside_point.size());
	SparseMatrix<double> Ay(inside_point.size(), inside_point.size());
	VectorXd Bx(inside_point.size());
	VectorXd By(inside_point.size());

	if (!inside_point.empty())
	{
		for (int i = 0; i < inside_point.size(); i++)//every inside point
		{
			double WEIGHT = 0;
			double wp_x = 0;
			double wp_y = 0;
			std::vector<double> id_weight[2];
			id_weight[0].clear();
			id_weight[1].clear();
			int onering_pointcount = 0;
			for (OMT::VVIter vv_it = copymesh->vv_iter(inside_point[i]); vv_it; vv_it++)//every inside point's one ring
			{
				int in = 0;
				int in_point = 0;
				onering_pointcount++;
				int pointA_confirm = 0;
				int pointC_confirm = 0;
				OMT::Point temp_pointA;
				OMT::Point temp_pointB = copymesh->point(vv_it.handle());
				OMT::Point temp_pointC;
				OMT::Point temp_pointM = copymesh->point(inside_point[i]);

				//if == middle point
				for (int c = 0; c < inside_point.size(); c++)
				{
					if (vv_it.handle() == inside_point[c] && c!=i)//if is inside point but not middle point
					{
						in = 1;
						in_point = c;
						id_weight[0].push_back(in_point);
						printf("%d: %d\n", i, in_point);
						break;
					}
				}
				for (Tri_Mesh::VertexOHalfedgeIter voh_it = copymesh->voh_iter(vv_it.handle()); voh_it; ++voh_it)
				{
					OMT::VertexHandle out_vh = copymesh->to_vertex_handle(voh_it.handle());
					
					for (OMT::VVIter vv_it2 = copymesh->vv_iter(inside_point[i]); vv_it2; vv_it2++)//inside point's one ring
					{
						//if on onering and != middle point
						if (out_vh == vv_it2.handle() && out_vh != inside_point[i] && pointA_confirm == 0)
						{
							temp_pointA = copymesh->point(out_vh);
							pointA_confirm = 1;
							break;
						}
						else if (out_vh == vv_it2.handle() && out_vh != inside_point[i] && pointA_confirm == 1)
						{
							temp_pointC = copymesh->point(out_vh);
							pointC_confirm = 1;
							break;
						}
					}
				}//find point A B C M end

				 //calculate weight 
				double vectorAM[3] = { temp_pointM[0] - temp_pointA[0],temp_pointM[1] - temp_pointA[1] ,temp_pointM[2] - temp_pointA[2] };
				double vectorAB[3] = { temp_pointB[0] - temp_pointA[0],temp_pointB[1] - temp_pointA[1] ,temp_pointB[2] - temp_pointA[2] };
				double vectorCM[3] = { temp_pointM[0] - temp_pointC[0],temp_pointM[1] - temp_pointC[1] ,temp_pointM[2] - temp_pointC[2] };
				double vectorCB[3] = { temp_pointB[0] - temp_pointC[0],temp_pointB[1] - temp_pointC[1] ,temp_pointB[2] - temp_pointC[2] };

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
				
				if (in == 1)
				{
					//copymesh->property(copymesh->weight_id, inside_point[in_point]) = weight_i;
					id_weight[1].push_back(weight_i);
				}
				//std::cout << "weight_i  " << weight_i << std::endl;
				
				WEIGHT += weight_i;
				//std::cout << vv_it.handle() << "handle" << std::endl;

				if (in == 0)//if is outside point
				{
					for (int i = 0; i < vh_v.size(); i++)
					{
						if (copymesh->property(copymesh->point_num, vv_it.handle()) == mesh_2d->property(mesh_2d->point_num_2d, vh_v[i]))
						{
							
							OMT::Point tmppoint = mesh_2d->point(vh_v[i]);
							wp_x += weight_i * tmppoint[0];
							wp_y += weight_i * tmppoint[1];
						}
					}
				}
				
				

				//calculate weight 
			}

			Ax.insert(i, i) = WEIGHT;
			Ay.insert(i, i) = WEIGHT;
			for (int p = 0; p < inside_point.size(); p++)
			{
				if (p != i)
				{
					for (int c = 0; c < id_weight[0].size(); c++)
					{
						if (id_weight[0][c] == p)
						{
							Ax.insert(i, p) = -id_weight[1][c];
							Ay.insert(i, p) = -id_weight[1][c];
							//std::cout << "p   " << p << std::endl;
						}
					}
					//Ax.insert(i, p) = -copymesh->property(copymesh->weight_id, inside_point[p]);
					//Ay.insert(i, p) = -copymesh->property(copymesh->weight_id, inside_point[p]);
				}

			}

			Bx[i] = wp_x;
			By[i] = wp_y;

		}

		std::cout << "Ax: " << Ax << std::endl;
		std::cout << "Bx: " << Bx << std::endl;

		Ax.makeCompressed();
		Ay.makeCompressed();

		

		SparseQR<SparseMatrix<double>, COLAMDOrdering<int>> linearSolver;
		linearSolver.compute(Ax);
		VectorXd X = linearSolver.solve(Bx);
		linearSolver.compute(Ay);
		VectorXd Y = linearSolver.solve(By);

		std::vector<OMT::VertexHandle> inside_point_2d;

		for (int i = 0; i < inside_point.size(); i++)
		{
			vh_v.push_back(mesh_2d->add_vertex(OMT::Point(X[i], Y[i], 0)));
			mesh_2d->property(mesh_2d->point_2d_id, vh_v[vh_v.size()-1])=copymesh->property(copymesh->copy_point_id,inside_point[i]);
		}
	}
	//calculate inside point position

	for (int n = 0; n < vh_v.size(); n++)
	{
		OMT::Point temp = mesh_2d->point(vh_v[n]);
		std::cout <<"2d coordinate"<< temp[0] << "  " << temp[1] << "  " << temp[2] <<"    point 2d id  "<< mesh_2d->property(mesh_2d->point_2d_id, vh_v[n]) <<std::endl;
	}
	
	std::cout << "face order size"<<face_order.size()  << std::endl;
	//add 2d new face
	std::vector<OMT::VertexHandle> temp_2d_vh;
	for (int i = 0; i < face_order.size(); i += 3)
	{
		
		temp_2d_vh.clear();
		
			for (int c = 0; c < vh_v.size(); c++)
			{
				if (face_order[i] == mesh_2d->property(mesh_2d->point_2d_id, vh_v[c]))
				{
					temp_2d_vh.push_back(vh_v[c]);
					break;
				}
			}
		
		
			for (int c = 0; c < vh_v.size(); c++)
			{
				if (face_order[i+1] == mesh_2d->property(mesh_2d->point_2d_id, vh_v[c]))
				{
					temp_2d_vh.push_back(vh_v[c]);
					break;
				}
			}
		
		
			for (int c = 0; c < vh_v.size(); c++)
			{
				if (face_order[i+2] == mesh_2d->property(mesh_2d->point_2d_id, vh_v[c]))
				{
					temp_2d_vh.push_back(vh_v[c]);
					break;
				}
			}
		
			fh_v.push_back(mesh_2d->add_face(temp_2d_vh));
			
	}

	for (int i = 0; i <vh_v.size();i++ )
	{
		for (int c = 0; c < const_copyvh.size(); c++)
		{
			if (mesh_2d->property(mesh_2d->point_2d_id, vh_v[i]) == copymesh->property(copymesh->copy_point_id, const_copyvh[c]))
			{
				OMT::Point temp2d=mesh_2d->point(vh_v[i]);
				copymesh->property(copymesh->bind_2d_to_3d, const_copyvh[c]) = temp2d;
			}
		}	
	}
	hkoglPanelControl2->Invalidate();
}
private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) 
{
	hkoglPanelControl4->Refresh();
	
	hair4= TextureApp::GenTexture("./fur1.jpg");
	hkoglPanelControl1->Refresh();
	hair1 = TextureApp::GenTexture("./fur1.jpg");
	hkoglPanelControl1->Invalidate();
	hkoglPanelControl4->Invalidate();
}
private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) 
{
	
	
}
private: System::Void button4_Click(System::Object^  sender, System::EventArgs^  e) 
{
	for (OMT::FIter f_it = copymesh->faces_begin(); f_it != copymesh->faces_end(); f_it++)
	{
		OMT::VertexHandle temp_copy_vhA;
		OMT::VertexHandle  temp_copy_vhB;
		OMT::VertexHandle  temp_copy_vhC;
		int A = 0, B = 0, C = 0;
		int texA = 0, texB = 0, texC = 0;
		for (OMT::FVIter fv_it = copymesh->fv_iter(f_it); fv_it; fv_it++)
		{
			if (A == 0)
			{
				temp_copy_vhA = fv_it;
				A = 1;
			}
			else if (A == 1 && B == 0)
			{
				temp_copy_vhB = fv_it;
				B = 1;
			}
			else if (A == 1 && B == 1 && C == 0)
			{
				temp_copy_vhC = fv_it;
				C = 1;
			}
		}
		OMT::Point temp_copyA = copymesh->point(temp_copy_vhA);
		OMT::Point temp_copyB = copymesh->point(temp_copy_vhB);
		OMT::Point temp_copyC = copymesh->point(temp_copy_vhC);
		OMT::Point temp_2dA = copymesh->property(copymesh->bind_2d_to_3d, temp_copy_vhA);
		OMT::Point temp_2dB = copymesh->property(copymesh->bind_2d_to_3d, temp_copy_vhB);
		OMT::Point temp_2dC = copymesh->property(copymesh->bind_2d_to_3d, temp_copy_vhC);
		/*mesh->set_texcoord2D(temp_copy_vhA, OpenMesh::Vec2f(temp_2dA[0], temp_2dA[1]));
		mesh->set_texcoord2D(temp_copy_vhB, OpenMesh::Vec2f(temp_2dB[0], temp_2dB[1]));
		mesh->set_texcoord2D(temp_copy_vhC, OpenMesh::Vec2f(temp_2dC[0], temp_2dC[1]));*/
		for (OMT::FVIter fv_it = copymesh->fv_iter(f_it); fv_it; fv_it++)
		{
			if (texA == 0)
			{
				copymesh->set_texcoord2D(fv_it.handle(), OpenMesh::Vec2f(temp_2dA[0], temp_2dA[1]));
				texA = 1;
				std::cout << "A" << temp_2dA[0] <<"  "<< temp_2dA[1] << std::endl;
			}
			else if (texA == 1 && texB == 0)
			{
				copymesh->set_texcoord2D(fv_it.handle(), OpenMesh::Vec2f(temp_2dB[0], temp_2dB[1]));
				texB = 1;
				std::cout << "B" << temp_2dB[0] << "  " << temp_2dB[1] << std::endl;
			}
			else if (texA == 1 && texB == 1 && texC == 0)
			{
				copymesh->set_texcoord2D(fv_it.handle(), OpenMesh::Vec2f(temp_2dC[0], temp_2dC[1]));
				texC = 1;
				std::cout << "C" << temp_2dC[0] << "  " << temp_2dC[1] << std::endl;
			}
		}


	}
	SaveFile("1.obj", copymesh);
		
}
private: System::Void button5_Click(System::Object^  sender, System::EventArgs^  e) 
{
	hkoglPanelControl1->Refresh();
	hkoglPanelControl2->Refresh();
	hkoglPanelControl4->Refresh();
	copymesh->clear_vh();

	copymesh = NULL;
	mesh_2d = NULL;
	
	
	
}
private: System::Void listBox1_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) 
{
	hkoglPanelControl1->Refresh();
}
private: System::Void button6_Click(System::Object^  sender, System::EventArgs^  e) 
{
	openModelDialog1->Filter = "Model(*.obj)|*obj";
	openModelDialog1->Multiselect = true;
	openModelDialog1->ShowDialog();
}
private: System::Void listBox2_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) 
{
	hkoglPanelControl1->Refresh();
}
private: System::Void hkoglPanelControl3_Load(System::Object^  sender, System::EventArgs^  e) 
{

}
private: System::Void hkoglPanelControl3_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) 
{
	glEnable(GL_COLOR_MATERIAL);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glDisable(GL_LIGHTING);

	point center;
	center[0] = 0.0;
	center[1] = 0.0;
	center[2] = 0.0;
	camera.setupGL(xf * center, 1.0);

	glPushMatrix();
	glMatrixMode(GL_MODELVIEW);
	glMultMatrixd((double *)xf);

	if (mesh != NULL)
	{
		mesh->Render_SolidWireframe();
	}
	if (done_mesh[0] != NULL)
	{
		for (size_t i = 0; i < donemesh; i++)
		{
			done_mesh[i]->Render_Texture(donetexture[idktexture[i]]);
		}
	}
	glPopMatrix();
}
private: System::Void hkoglPanelControl3_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) 
{
	int Op_X, Op_Y;
	Op_X = e->X;
	Op_Y = hkoglPanelControl3->Height - e->Y;

	if (e->Button == System::Windows::Forms::MouseButtons::Left ||
		e->Button == System::Windows::Forms::MouseButtons::Middle)
	{
		point center;
		Mouse_State = Mouse::NONE;
		center[0] = 0.0;
		center[1] = 0.0;
		center[2] = 0.0;
		camera.mouse(e->X, e->Y, Mouse_State,
			xf * center,
			1.0, xf);
		//hkoglPanelControl3->Invalidate();
	}
}
private: System::Void hkoglPanelControl3_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) 
{
	if (e->Button == System::Windows::Forms::MouseButtons::Left)
	{
		point center;
		Mouse_State = Mouse::ROTATE;
		center[0] = 0.0;
		center[1] = 0.0;
		center[2] = 0.0;
		camera.mouse(e->X, e->Y, Mouse_State,
			xf * center,
			1.0, xf);
		//hkoglPanelControl3->Invalidate();
	}

	if (e->Button == System::Windows::Forms::MouseButtons::Middle)
	{
		point center;
		Mouse_State = Mouse::MOVEXY;
		center[0] = 0.0;
		center[1] = 0.0;
		center[2] = 0.0;
		camera.mouse(e->X, e->Y, Mouse_State,
			xf * center,
			1.0, xf);
		//hkoglPanelControl3->Invalidate();
	}
}

private: System::Void hkoglPanelControl3_MouseWheel(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
{
	if (e->Delta < 0)
	{
		point center;
		Mouse_State = Mouse::WHEELDOWN;
		center[0] = 0.0;
		center[1] = 0.0;
		center[2] = 0.0;
		camera.mouse(e->X, e->Y, Mouse_State,
			xf * center,
			1.0, xf);
		//hkoglPanelControl1->Invalidate();
		//hkoglPanelControl3->Invalidate();
		//hkoglPanelControl2->Invalidate();
	}
	else
	{
		point center;
		Mouse_State = Mouse::WHEELUP;
		center[0] = 0.0;
		center[1] = 0.0;
		center[2] = 0.0;
		camera.mouse(e->X, e->Y, Mouse_State,
			xf * center,
			1.0, xf);
		//hkoglPanelControl1->Invalidate();
		//hkoglPanelControl3->Invalidate();
		//hkoglPanelControl2->Invalidate();
	}
}
private: System::Void button3_Click_1(System::Object^  sender, System::EventArgs^  e) 
{
	if (listBox1->SelectedIndex != -1 && listBox2->SelectedIndex != -1) {
		done_mesh[donemesh] = new Tri_Mesh;
		done_mesh[donemesh] = temp_mesh[listBox1->SelectedIndex];
		idktexture[donemesh] = listBox2->SelectedIndex;
		
		/*done_mesh[donemesh]->setBoundaryVOrder();
		done_mesh[donemesh]->setOutsidePoint();
		done_mesh[donemesh]->setweight();
		done_mesh[donemesh]->SolveLinear();*/
		
		donemesh++;
		puts("1");
		hkoglPanelControl3->Refresh();
		hkoglPanelControl3->Invalidate();
		//hkoglPanelControl3->Invalidate();
	}
}
private: System::Void MyForm_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) 
{
	listBox1->SelectedIndex = -1;
	listBox2->SelectedIndex = -1;
}
private: System::Void button7_Click(System::Object^  sender, System::EventArgs^  e) 
{
	openFileDialog->Multiselect = true;
	openFileDialog->ShowDialog();
}
};
}

