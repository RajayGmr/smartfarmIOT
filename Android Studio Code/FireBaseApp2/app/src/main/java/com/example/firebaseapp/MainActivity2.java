package com.example.firebaseapp;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Spinner;

import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.ValueEventListener;

public class MainActivity2 extends AppCompatActivity {
    private EditText editTextNumber;
    private EditText editTextTextPersonName2;
    private Button button7;
    private Button button8;
    private Button button9;
    private Spinner spinner;
    private Spinner spinner2;
    FirebaseDatabase database=FirebaseDatabase.getInstance();
    DatabaseReference myRef=database.getReference().child("DAY1");

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main2);
        editTextNumber=findViewById(R.id.editTextNumber);
        editTextTextPersonName2=findViewById(R.id.editTextTextPersonName2);
        button7=findViewById(R.id.button7);
        button8=findViewById(R.id.button8);
        button9=findViewById(R.id.button9);
        Spinner spinner=findViewById(R.id.spinner);
        Spinner spinner2=findViewById(R.id.spinner2);


        String[] day=new String[]{"DAY1","DAY2","DAY3","DAY4","DAY5",
                "DAY6","DAY7","DAY8","DAY9","DAY10",
                "DAY11","DAY12","DAY13","DAY14","DAY15",
                "DAY16","DAY17","DAY18","DAY19","DAY20",
                "DAY21","DAY22","DAY23","DAY24","DAY25",
                "DAY26","DAY27","DAY28","DAY29","DAY30",
                "DAY31","DAY32","DAY33","DAY34","DAY35",
                "DAY36","DAY37","DAY38","DAY39","DAY40"};

        ArrayAdapter<String> adapter = new ArrayAdapter<>(this,
                android.R.layout.simple_spinner_dropdown_item,day);
        spinner.setAdapter(adapter);

        String[] time=new String[]{"timeslot1","timeslot2",
                "timeslot3","timeslot4","timeslot5"};

        ArrayAdapter<String> adapter1 = new ArrayAdapter<>(this,
                android.R.layout.simple_spinner_dropdown_item,time);
        spinner2.setAdapter(adapter1);
//ok
        button7.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                saveData();

            }
        });
        //load
        button8.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                myRef.addValueEventListener(new ValueEventListener() {
                    @Override
                    public void onDataChange(@NonNull DataSnapshot snapshot) {
                        String DAY=snapshot.child("DAY1").getValue().toString();
                        editTextTextPersonName2.setText(DAY);
                    }
                    @Override
                    public void onCancelled(@NonNull DatabaseError error) {

                    }
                });
            }
        });

        button9.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
               Back();
            }
        });
    }
    public void Back(){
        Intent intent=new Intent(this, MainActivity.class);
        startActivity(intent);
    }
    public void saveData(){

    }
}